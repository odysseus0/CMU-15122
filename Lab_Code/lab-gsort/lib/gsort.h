/*
 * Generic sorting
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include <stdbool.h>

#ifndef _GSORT_H_
#define _GSORT_H_

// Swaps the objects at memory locations x and y
typedef void swap_fn(void *x, void *y)
  /*@requires x != NULL && y != NULL; @*/ ;

// Compares the objects at memory locations x and y
typedef int compare_fn(void *x, void *y)
  /*@requires x != NULL && y != NULL; @*/
  /*@ensures -1 <= \result && \result <= 1; @*/ ;

void gsort(void *A, size_t count, size_t elt_size,
           swap_fn *swp, compare_fn *cmp)
  /*@requires A != NULL && swp != NULL && cmp != NULL; @*/
  /* requires that A is an allocation of at least count * elt_size */ ;

#endif
