/*
 * Interface for generic stacks
 * You'll want to use these to implement call stacks
 * 
 * We can't call these stack_t because there's a type in the C
 * standard libraries named stack_t, ugh.
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>

#ifndef _STACK_H_
#define _STACK_H_

/*********************/
/* Client interface */
/*********************/

// typedef ______ stack_elem;
typedef void *stack_elem;

typedef void stack_elem_free_fn(stack_elem x);

/*********************/
/* Library interface */
/*********************/

// typedef ______* gstack_t;
typedef struct stack_header *gstack_t;

bool stack_empty(gstack_t S)
  /*@requires S != NULL; @*/ ;

gstack_t stack_new()
  /*@ensures \result != NULL; @*/ ;

void push(gstack_t S, stack_elem x) 
  /*@requires S != NULL; @*/ ;

stack_elem pop(gstack_t S)
  /*@requires S != NULL; @*/ ;

size_t stack_size(gstack_t S)
  /*@requires S != NULL; */ ;

void stack_free(gstack_t S, stack_elem_free_fn* elem_free)
  /*@requires S != NULL; @*/ 
  /* if elem_free is NULL, then elements will not be freed */ ;

#endif
