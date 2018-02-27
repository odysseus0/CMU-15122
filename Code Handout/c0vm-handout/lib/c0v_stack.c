/* 
 * Interface for stacks of type c0_value, specifically
 *
 * 15-122 Principles of Imperative Computation 
 */

#include <stdlib.h>
#include <stdbool.h>
#include "xalloc.h"
#include "contracts.h"
#include "c0v_stack.h"
#include "c0vm.h"

/* Aux structure of linked lists */
typedef struct list_node list;
struct list_node {
  c0_value data;
  struct list_node *next;
};

/* will diverge if list is circular! */
static inline bool is_stack_segment(list *start, list *end)
{
  list *p = start;
  while (p != end) {
    if (p == NULL) return false;
    p = p->next;
  }
  return true;
}

/* Stacks */ 

typedef struct c0v_stack_header stack;
struct c0v_stack_header {
  list *top;
  list *bottom;
};

bool is_c0v_stack (stack *S) {
  if (S == NULL) return false;
  if (S->top == NULL || S->bottom == NULL) return false;
  if (!is_stack_segment(S->top, S->bottom)) return false;
  return true;
}

bool c0v_stack_empty(stack *S) {
  REQUIRES(is_c0v_stack(S));
  return S->top == S->bottom;
}

stack *c0v_stack_new() {
  stack *S = xmalloc(sizeof(stack));
  list *p = xmalloc(sizeof(list));
  /* Dummy node: does not need to be initialized! */
  S->top = p;
  S->bottom = p;

  ENSURES(is_c0v_stack(S));
  ENSURES(c0v_stack_empty(S));
  return S;
}

void c0v_push(stack *S, c0_value x) {
  REQUIRES(is_c0v_stack(S));

  list *p = xmalloc(sizeof(list));
  p->data = x;
  p->next = S->top;
  S->top = p;

  ENSURES(is_c0v_stack(S) && !c0v_stack_empty(S));
}

c0_value c0v_pop(stack *S) {
  REQUIRES(is_c0v_stack(S));
  REQUIRES(!c0v_stack_empty(S));

  c0_value x = S->top->data;    /* save old stack element to return */
  list *q = S->top;             /* save old list node to free */
  S->top = S->top->next;
  free(q);                      /* free old list node */

  ENSURES(is_c0v_stack(S));
  return x;                     /* return old stack element */
}

size_t c0v_stack_size(stack *S) {
  REQUIRES(is_c0v_stack(S));

  size_t i = 0;
  for (list *p = S->top; p != S->bottom; p = p->next) i++;
  return i;
}

void c0v_stack_free(stack *S) {
  REQUIRES(is_c0v_stack(S));

  while (S->top != S->bottom) {
    ASSERT(is_stack_segment(S->top, S->bottom));
    list *p = S->top;
    S->top = S->top->next;
    free(p);
  }

  free(S->top); /* == S->bottom */
  free(S);
}
