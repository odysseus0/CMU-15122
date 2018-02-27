/*
 * Hash dicts implementation
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "xalloc.h"
#include "contracts.h"
#include "hdict.h"

struct chain_node {
  hdict_key key;
  hdict_value value;
  struct chain_node* next;
};
typedef struct chain_node chain;

typedef struct hdict_header hdict;
struct hdict_header {
  size_t size;
  size_t capacity;               /* 0 < capacity */
  chain **table;             /* \length(table) == capacity */
  key_equal_fn *key_equal;
  key_hash_fn *key_hash;
  value_free_fn *value_free;
};

static inline size_t hashindex(hdict* H, hdict_key x) {
  REQUIRES(H != NULL && H->capacity > 0 && H->key_hash != NULL);
  return (*H->key_hash)(x) % H->capacity;
}

static inline bool keyequal(hdict* H, hdict_key x, hdict_key y) {
  REQUIRES(H != NULL && H->capacity > 0 && H->key_equal != NULL);
  return (*H->key_equal)(x, y);
}

static bool is_chain(hdict* H, chain* p, size_t i) {
  REQUIRES (H != NULL && H->capacity > 0 && H->key_hash != NULL);
  for (chain* q = p; q != NULL; q = q->next) {
    if (q->key == NULL) return false;
    if (hashindex(H, p->key) != i) { 
      fprintf(stderr, "Violation: key in index %zu claims ", i);
      fprintf(stderr, "to belong in index %zu.\n", hashindex(H, p->key));
      fprintf(stderr, "This indicates that client code modifies data ");
      fprintf(stderr, "in the hashtable.\n");
      return false;
    }
  }
  return true;
}

static bool is_chains(hdict* H, size_t lo, size_t hi) {
  REQUIRES(H != NULL && H->capacity > 0 && H->key_hash != NULL);
  REQUIRES(lo <= hi && hi <= H->capacity);
  for (size_t i = lo; i < hi; i++) {
    if (!is_chain(H, H->table[i], i)) return false;
  }
  return true;
}

bool is_hdict(hdict* H) {
  return  H != NULL
    && H->capacity > 0
    && H->key_equal != NULL
    && H->key_hash != NULL
    && is_chains(H, 0, H->capacity);
}

hdict* hdict_new(size_t capacity,  
                 key_equal_fn *key_equal,
                 key_hash_fn *key_hash, 
                 value_free_fn *value_free) {
  REQUIRES(capacity > 0 && key_equal != NULL && key_hash != NULL);

  hdict* H = xmalloc(sizeof(struct hdict_header));
  H->size = 0;
  H->capacity = capacity;
  H->table = xcalloc(capacity, sizeof(chain*));
  H->key_equal = key_equal;
  H->key_hash = key_hash;
  H->value_free = value_free;

  ENSURES(is_hdict(H));
  return H;
}

hdict_key hdict_lookup(hdict* H, hdict_key x) {
  REQUIRES(is_hdict(H) && x != NULL);
  
  int i = hashindex(H, x);
  for (chain* p = H->table[i]; p != NULL; p = p->next) {
    if (keyequal(H, p->key, x)) {
      return p->value;
    }
  }

  return NULL;
}

static inline void hdict_resize(hdict* H, size_t new_capacity) {
  REQUIRES(is_hdict(H));
  REQUIRES(new_capacity > 0);

  chain** old_table = H->table;
  chain** new_table = xcalloc(new_capacity, sizeof(chain*));
  size_t old_capacity = H->capacity;
  H->capacity = new_capacity; // is_hdict now violated!

  for (size_t i = 0; i < old_capacity; i++) {
    chain* p_next;
    for (chain* p = old_table[i]; p != NULL; p = p_next) {
      hdict_key x = p->key;
      p_next = p->next;
      size_t h = hashindex(H, x);
      p->next = new_table[h];
      new_table[h] = p;
      p = p_next;
    }
  }

  H->table = new_table;
  free(old_table);
}

hdict_value hdict_insert(hdict* H, hdict_key k, hdict_value v) {
  REQUIRES(is_hdict(H));
  
  int i = hashindex(H, k);
  for (chain* p = H->table[i]; p != NULL; p = p->next) {
    if (keyequal(H, p->key, k)) {
      hdict_key old = p->value;
      p->value = v;

      ENSURES(is_hdict(H));
      ENSURES(hdict_lookup(H, k) == v);
      return old;
    }
  }
  
  // prepend new key
  chain* p = xmalloc(sizeof(chain));
  p->key = k;
  p->value = v;
  p->next = H->table[i];
  H->table[i] = p;
  (H->size)++;

  if (H->size > H->capacity && H->capacity < UINT_MAX / 2) {
    hdict_resize(H, 2*H->capacity);
  }

  ENSURES(is_hdict(H));
  ENSURES(hdict_lookup(H, k) == v);
  return NULL;
}

void hdict_free(hdict* H) {
  REQUIRES(is_hdict(H));

  for (size_t i = 0; i < H->capacity; i++) {
    chain* p_next;
    for (chain* p = H->table[i]; p != NULL; p = p_next) {
      if (H->value_free != NULL) (*H->value_free)(p->value);
      p_next = p->next;
      free(p);
    }
  }

  free(H->table);
  free(H);
}


