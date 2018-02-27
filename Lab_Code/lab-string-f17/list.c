#include <stdlib.h>
#include <stdio.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"

typedef struct list_header list;
struct list_header {
  void *data;
  list *next;
};


/* TRANSLATE THE CONTRACTS BELOW */

int length(list* start, list* end)
//@requires is_segment(start, end);
////@ensures \result > 0;
{
  int length = 0;
  while (start != end)
  //@loop_invariant is_segment(start, end);
  {
    length++;
    start = start->next;
  }
  return length;
}


int main() {
  printf("You can write your own tests in list.c if you want.\n");
}
