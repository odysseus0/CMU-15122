/*
 * Hash dicts interface
 * 
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _HDICT_H_
#define _HDICT_H_

typedef void *hdict_key;
typedef void *hdict_value;
typedef bool key_equal_fn(hdict_key x, hdict_key y);
typedef size_t key_hash_fn(hdict_key x);
typedef void value_free_fn(hdict_value x);

typedef struct hdict_header* hdict_t;

hdict_t hdict_new(size_t capacity,
                  key_equal_fn *key_equal,
                  key_hash_fn *key_hash,
                  value_free_fn *value_free)
  /*@requires capacity > 0; @*/ 
  /*@requires elem_equal != NULL && elem_hash != NULL; @*/
  /* if elem_free is NULL, then elements will not be freed */
  /*@ensures \result != NULL; @*/ ;

/* If insertion removes an existing element from the dict, that
 * removed element will be returned so that the client can free it, if
 * necessary */
hdict_value hdict_insert(hdict_t H, hdict_key k, hdict_value v)
  /*@requires H != NULL; @*/ ;

hdict_value hdict_lookup(hdict_t H, hdict_key x)
  /*@requires H != NULL; @*/ ;

void hdict_free(hdict_t H)
  /*@requires H != NULL; @*/ ;

#endif
