/*
 * Testing Union-Find
 * 
 * 15-122 Principles of Imperative Computation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "unionfind.h"

int main () {
  int n = 6;
  ufs eqs = singletons(n);
  ufs_union(eqs, 0, 1);
  ufs_union(eqs, 1, 2);
  ufs_union(eqs, 0, 2);
  ufs_union(eqs, 3, 4);
  ufs_union(eqs, 2, 3);
  ufs_union(eqs, 3, 5);
  for (int i = 0; i < n-1; i++)
    assert(ufs_find(eqs,i) == ufs_find(eqs,i+1)); // a spanning tree?
  ufs_free(eqs);

  n = 1<<12;
  eqs = singletons(n);
  for(int i = 0; i < n-1; i++)
    ufs_union(eqs, i, i+1);
  assert(ufs_find(eqs, 0) == ufs_find(eqs, n-1));

  printf("All tests passed!\n");
  return 0;
}
