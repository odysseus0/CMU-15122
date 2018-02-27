/* Allocation utilities
 * Implement versions of malloc and free that abort
 * when allocation fails instead of returning NULL.
 *
 * 15-122 Principles of Imperative Computation
 */
#include <stdio.h>

#ifndef _XALLOC_H_
#define _XALLOC_H_

/* xcalloc(nobj, size) returns a pointer to array of nobj objects,
 * each of size size and exits if the allocation fails.  Like calloc,
 * the array is initialized with zeroes.
 */
void* xcalloc(size_t nobj, size_t size)
  /*@ensures \result != NULL; @*/ ;

/* xmalloc(size) returns a pointer to an object of size size and exits
 * if the allocation fails.  Like malloc, no initialization is
 * guaranteed.
 */
void* xmalloc(size_t size)
  /*@ensures \result != NULL; @*/ ;

#endif
