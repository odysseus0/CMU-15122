/*
 * Unbounded priority queues interface, implemented as heaps
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _HEAP_H_
#define _HEAP_H_

/*********************/
/* Client interface */
/*********************/

// typedef ______ heap_elem;
typedef void *heap_elem;

// f(x,y) returns true if x is STRICTLY higher priority than y
typedef bool higher_priority_fn(heap_elem x, heap_elem y);

typedef void heap_elem_free_fn(heap_elem x);

/*********************/
/* Library interface */
/*********************/

// typedef ______* heap_t;
typedef struct heap_header *heap_t;

bool heap_empty(heap_t H)
  /*@requires H != NULL; @*/ ;

heap_t heap_new(higher_priority_fn *prior, heap_elem_free_fn *elem_free)
  /*@requires prior != NULL; @*/ 
  /* if elem_free is NULL, then elements will not be freed */
  /*@ensures \result != NULL && heap_empty(\result); @*/ ;

void heap_add(heap_t H, heap_elem x)
  /*@requires H != NULL; @*/ ;

heap_elem heap_rem(heap_t H)
  /*@requires H != NULL && !heap_empty(H); @*/ ;

void heap_free(heap_t H)
  /*@requires H != NULL; @*/ ;

#endif
