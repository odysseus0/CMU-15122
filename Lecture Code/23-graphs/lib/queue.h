/* 
 * Queues of unsigned integers
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>

#ifndef _QUEUE_H_
#define _QUEUE_H_

/*********************/
/* Client interface */
/*********************/

// typedef ______ queue_elem;
typedef unsigned int queue_elem;

/*********************/
/* Library interface */
/*********************/

// typedef ______* queue_t;
typedef struct queue_header *queue_t;

bool queue_empty(queue_t Q)
  /*@requires Q != NULL; @*/ ;

queue_t queue_new()
  /*@ensures \result != NULL; @*/ ;

void enq(queue_t Q, queue_elem x) 
  /*@requires Q != NULL; @*/ ;

queue_elem deq(queue_t Q)
  /*@requires Q != NULL; @*/ ;

void queue_free(queue_t Q)
  /*@requires Q != NULL; @*/ 
  /* if elem_free is NULL, then elements will not be freed */ ;

#endif
