/*
 * Stacks of unsigned integers
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>

#ifndef _STACK_H_
#define _STACK_H_

/*********************/
/* Client interface */
/*********************/

// typedef ______ stack_elem;
typedef unsigned int stack_elem;

typedef void stack_elem_free_fn(stack_elem x);

/*********************/
/* Library interface */
/*********************/

// typedef ______* istack_t;
typedef struct stack_header *istack_t;

bool stack_empty(istack_t S)
  /*@requires S != NULL; @*/ ;

istack_t stack_new()
  /*@ensures \result != NULL; @*/ ;

void push(istack_t S, stack_elem x) 
  /*@requires S != NULL; @*/ ;

stack_elem pop(istack_t S)
  /*@requires S != NULL; @*/ ;

size_t stack_size(istack_t S)
  /*@requires S != NULL; */ ;

void stack_free(istack_t S)
  /*@requires S != NULL; @*/ 
  /* if elem_free is NULL, then elements will not be freed */ ;

#endif
