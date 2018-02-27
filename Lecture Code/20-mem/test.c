#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"

struct point {
    int x;
    int y;
  };

void increment(int *p) {
  //  REQUIRES(p != NULL);
  *p = *p + 1;
}

/*
// Used to be legal, now doesn't compile
int *bad() {
  int a = 1;
  return &a;
}
*/

int main() {

  // Arrays and pointer arithmetic
//  int *A = xmalloc(sizeof(int) * 5);  // Does not initialize array
  int *A = xcalloc(5, sizeof(int));     // Initializes array

  A[1] = 7;
  *(A+2) = *(A+1) + 5;
  *A = 42;
  A[3] = *A - 5;
  4[A] = 257;

  for (int i=0; i < 5; i++)
    printf("A[%d] is %d\n", i, A[i]);

  //printf("A[...] is %d\n", A[5]);         // Out of bounds read  (V)
  //printf("A[...] is %d\n", A[1000]);      // Out of bounds read  (V)
  //printf("A[...] is %d\n", A[-1]);        // Out of bounds read  (V)

  //printf("A[...] is %d\n", A[10000000]);  // segfault            (V!)

  //A[5] = 15122;                           // Out of bounds write (V)
  //printf("A[...] is %d\n", A[5]);         // Out of bounds read  (V)

  //A[100] = 42;                            // Out of bounds write (no V!)
  //printf("A[...] is %d\n", A[100]);       // Out of bounds read  (V)


  // Aliasing
  int *B = A + 2;
  ASSERT(B[0] == A[2]);
  ASSERT(B[1] == A[3]);
  ASSERT(B + 1 == A + 3);
  ASSERT(*(B + 2) == A[4]);
  // free(B);                               // Unallocated memory!


  // Pointer casting
  char *C = (char *)A;
  printf("The 16th char in C is '%d'\n", C[16]);
  struct point *D = (struct point *)(A + 2);
  printf("(x1,y1) = (%d, %d)\n", D[0].x, D[0].y);
  //printf("(x2,y2) = (%d, %d)\n", D[1].x, D[1].y);  // Out of bound read

  //thermonuclear_device_controller *danger = (thermonuclear_device_controller *)A; // !!!!


  // Stack-allocated arrays
  int n = 10;
  int E[n];
  for (int i=0; i<n; i++)
    E[i] = i*i;
  (void)E;

  int F[] = {1, 2, 3, 4, 5};
  (void)F;


  // Strings
  char *s1 = "hellowwww";                   // Text-allocated (read-only)
  char *s2 = malloc(strlen(s1) + 1);        // Heap-allocated
  char s3[] = "world";                      // Stack-allocated
  char s4[] = {'f', 'i', 'n', 'e', '\0'};   // Stack-allocated
  // s1[0] = 'm';                           // Writing to read-only memory
  strcpy(s2, s1);
  s2[0] = 'Y';
  printf("%s became %s\n", s1, s2);
  s3[2] = 'u';
  printf("%s %s\n", s4, s3);
  free(s2);


  // Stack-allocated structs
  struct point p;
  p.x = 3;
  p.y = 7;
  printf("p is (%d,%d)\n", p.x, p.y);


  // Address-of
  int i = 42;
  increment(&i);
  printf("i = %d\n", i);

  increment(&p.y);
  printf("p is (%d,%d)\n", p.x, p.y);


  free(A);
}
