/*
 * Union-Find
 * 15-122 Principles of Imperative Computation, Fall 2012
 * Frank Pfenning
 *
 */

#include <stdbool.h>

#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

typedef struct ufs_header *ufs_t;

ufs_t singletons(unsigned int n);

bool ufs_elem(ufs_t eqs, int i);

int ufs_find(ufs_t eqs, int i); 
//@requires ufs_elem(eqs, i);
//@ensures ufs_elem(eqs, \result);

void ufs_union(ufs_t eqs, int i, int k);
//@requires ufs_elem(eqs, i) && ufs_elem(eqs, k);

void ufs_free(ufs_t eqs);

#endif
