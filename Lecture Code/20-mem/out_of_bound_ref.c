#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"

int main() {

  // Arrays and pointer arithmetic
//  int *A = xmalloc(sizeof(int) * 5);  // Does not initialize array
  int *A = xcalloc(5, sizeof(int));     // Initializes array

  A[1] = 7;
  *(A+2) = *(A+1) + 5;
  *A = 42;
  A[3] = *A - 5;
  4[A] = 257;
}

