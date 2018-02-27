#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lib/gsort.h"
#include "lib/contracts.h"

int compare_int(void *x, void *y) {
  REQUIRES(x != NULL && y != NULL);
  if (*(int*)x < *(int*)y) return -1;
  if (*(int*)x == *(int*)y) return 0;
  return 1;
}

void swap_int(void *x, void *y) {
  REQUIRES(x != NULL && y != NULL);
  int *a = x;
  int *b = y;
  int temp = *a;
  *a = *b;
  *b = temp;
}

int compare_char(void *x, void *y) {
  REQUIRES(x != NULL && y != NULL);
  if (*(char*)x < *(char*)y) return -1;
  if (*(char*)x == *(char*)y) return 0;
  return 1;
}

void swap_char(void *x, void *y) {
  REQUIRES(x != NULL && y != NULL);
  char *a = x;
  char *b = y;
  char temp = *a;
  *a = *b;
  *b = temp;
}

typedef struct frequency_information freqinfo;
struct frequency_information {
  char *word;
  int count;
};

void print_ints(int *A, size_t len) {
  if (len == 0) { printf("{}"); return; }

  printf("{ %d", A[0]);
  for (size_t i = 1; i < len; i++) {
    printf(", %d", A[i]);
  }
  printf(" }\n\n");
}

void print_freqinfos(freqinfo *A, size_t len) {
  for (size_t i = 0; i < len; i++) {
    printf("\"%s\" has frequency %d\n", A[i].word, A[i].count);
  }
  printf("\n");
}

int main() {
  char A[] = "the quick brown fox jumped over the lazy dog<---sort this";
  int B[] = {42, 1, 3, 7, 2, 45, 1, 16, 92, 4};
  
  printf("The array A: \"%s\"\n\n", A);
  gsort(A, 44, sizeof(char), &swap_char, &compare_char); 
  printf("The array A, initial part sorted:\n%s\n\n", A);
  gsort(A, 57, sizeof(char), &swap_char, &compare_char);
  printf("The array A, sorted all the way to the NUL terminator:\n%s\n\n", A);
  
  printf("The array B: ");
  print_ints(B, 10);
  
  gsort(B, 3, sizeof(int), &swap_int, &compare_int);
  printf("The array B, first 3 elements sorted: ");
  print_ints(B, 10);

  gsort(B, 10, sizeof(int), &swap_int, &compare_int);
  printf("The array B, all elements sorted: ");
  print_ints(B, 10);

  return 0; // <--- For final task, remove this line!

  freqinfo C[] = { { .word = "the",  .count = 22038615 },
                   { .word = "be",   .count = 12545825 },
                   { .word = "and",  .count = 10741073 },
                   { .word = "of",   .count = 10343885 },
                   { .word = "a",    .count = 10144200 },
                   { .word = "in",   .count = 6996437 },
                   { .word = "to",   .count = 6332195 },
                   { .word = "have", .count = 4303955 },
                   { .word = "it",   .count = 3872477 },
                   { .word = "i",    .count = 3978265 },
                   { .word = "that", .count = 3430996 },
                   { .word = "for",  .count = 3281454 },
                   { .word = "you",  .count = 3081151 },
                   { .word = "with", .count = 2683014 } };

  // Sort by frequency
  printf("Sorted by frequency:\n");
  print_freqinfos(C, 14);

  // Sort by word
  printf("Sorted by string:\n");
  print_freqinfos(C, 14);

  return 0;
}
