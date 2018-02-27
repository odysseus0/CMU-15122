/*
 * Interface for stacks of type c0_value, specifically
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include "c0vm.h"

#ifndef _VALSTACK_H_
#define _VALSTACK_H_

// typedef ______* c0v_stack_t;
typedef struct c0v_stack_header *c0v_stack_t;

bool c0v_stack_empty(c0v_stack_t S)
  /*@requires S != NULL; @*/ ;

c0v_stack_t c0v_stack_new()
  /*@ensures \result != NULL; @*/ ;

void c0v_push(c0v_stack_t S, c0_value x) 
  /*@requires S != NULL; @*/ ;

c0_value c0v_pop(c0v_stack_t S)
  /*@requires S != NULL; @*/ ;

size_t c0v_stack_size(c0v_stack_t S)
  /*@requires S != NULL; */ ;

void c0v_stack_free(c0v_stack_t S) /* Does not free anything */
  /*@requires S != NULL; @*/ ;

#endif
