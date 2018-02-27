/*
 * Simple test case
 *
 * 15-122 Principles of Imperative Computation */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "lib/xalloc.h"
#include "simple.h"

int main() {
  // free(P);  // wrong!
  struct point2d* P = xmalloc(sizeof(struct point2d));
  P->x = -15;
  P->y = P->y + absval(P->x * 2);
  assert(P->y > P->x && true);

  // free(P);  // wrong!
  printf("x coord: %d\n", P->x);
  printf("y coord: %d\n", P->y);  // uninitialized: could print anything

  free(P);

  return 0;
}
