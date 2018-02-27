/*
 * Unbounded priority queues interface, implemented as heaps
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "xalloc.h"
#include "contracts.h"
#include "heap.h"

typedef struct heap_header heap;
struct heap_header {
  size_t limit;                 /* limit = capacity+1 */
  size_t next;                  /* 1 <= next && next <= limit */
  heap_elem *data;              /* \length(data) == limit */
  higher_priority_fn *prior;    /* Not NULL */
  heap_elem_free_fn *elem_free; /* May be NULL */
};

bool is_safe_heap(heap *H) {
  return H != NULL
    && 1 <= H->next && H->next <= H->limit
    && H->prior != NULL;
}

/* Returns true if the element in H->data[i] can
 * correctly be placed above H->data[j] in the heap. */
inline static bool ok_above(heap *H, size_t i, size_t j) {
  REQUIRES(is_safe_heap(H));
  REQUIRES(1 <= i && i < H->next);
  REQUIRES(1 <= j && j < H->next);
  return !(*H->prior)(H->data[j], H->data[i]);
}

inline static void swap_up(heap *H, size_t i) {
  heap_elem tmp = H->data[i];
  H->data[i] = H->data[i/2];
  H->data[i/2] = tmp;
}

bool is_heap(heap *H) {
  if (!is_safe_heap(H)) return false;
  for (size_t i = 2; i < H->next; i++)
    if (!ok_above(H, i/2, i)) return false;
  return true;
}

bool heap_empty(heap *H) {
  REQUIRES(is_heap(H));
  return H->next == 1;
}

heap *heap_new(higher_priority_fn *prior, heap_elem_free_fn *elem_free) {
  REQUIRES(prior != NULL);
  heap *H = xmalloc(sizeof(heap));
  H->limit = 4;
  H->next = 1;
  H->data = xcalloc(H->limit, sizeof(heap_elem));
  H->prior = prior;
  H->elem_free = elem_free;
  ENSURES(is_heap(H));
  return H;
}

static inline void heap_resize(heap *H, size_t new_limit) {
  REQUIRES(is_heap(H));

  heap_elem *new_data = xcalloc(new_limit, sizeof(heap_elem));

  for (size_t i = 0; i < H->next; i++)
    new_data[i] = H->data[i];

  free(H->data);
  H->limit = new_limit;
  H->data = new_data;

  ENSURES(is_heap(H));
}

void heap_add(heap *H, heap_elem x)
//@requires is_heap(H);
//@ensures is_heap(H);
{
  if (H->next == H->limit) {
    assert(H->next < SIZE_MAX / 2);
    heap_resize(H, 2*H->limit);
  }

  int i = H->next;
  H->data[H->next] = x;
  (H->next)++;
  /* H is no longer a heap! */

  while (i > 1) {
    if (ok_above(H, i/2, i)) break;
    swap_up(H, i);
    i = i/2;
  }

  ENSURES(is_heap(H));
}

static inline void sift_down(heap *H) {
  REQUIRES(is_safe_heap(H) && H->next > 1);
  size_t i = 1;

  while (2*i < H->next) {
    size_t left = 2*i;
    size_t right = left+1;

    if (ok_above(H, i, left)
        && (right >= H->next || ok_above(H, i, right))) {
      return;
    } else if (right >= H->next || ok_above(H, left, right)) {
      swap_up(H, left);
      i = left;
    } else {
      ASSERT(right < H->next && ok_above(H, right, left));
      swap_up(H, right);
      i = right;
    }
  }

  ENSURES(is_heap(H));
}

heap_elem heap_rem(heap *H) {
  REQUIRES(is_heap(H) && !heap_empty(H));
  heap_elem x = H->data[1];
  (H->next)--;

  if (H->next > 1) {
    H->data[1] = H->data[H->next];
    sift_down(H);
  }

  if (H->limit % 4 == 0 && H->next < H->limit / 4)
    heap_resize(H, H->limit / 2);

  ENSURES(is_heap(H));
  return x;
}

void heap_free(heap *H) {
  REQUIRES(is_heap(H));

  if (H->elem_free != NULL) {
    for (size_t i = 1; i < H->next; i++) {
      (*H->elem_free)(H->data[i]);
    }
  }

  free(H->data);
  free(H);
}
