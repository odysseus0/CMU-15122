/* 
 * Queues 
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>
#include "xalloc.h"
#include "contracts.h"
#include "queue.h"

/* Aux structure of linked lists */
typedef struct list_node list;
struct list_node {
  queue_elem data;
  struct list_node *next;
};

/* will diverge if list is circular! */
bool is_queue_segment(list *start, list *end)
{
  list *p = start;
  while (p != end) {
    if (p == NULL) return false;
    p = p->next;
  }
  return true;
}

/* Queues */ 

typedef struct queue_header queue;
struct queue_header {
  list *front;
  list *back;
};

bool is_queue (queue *Q) {
  if (Q == NULL) return false;
  if (Q->front == NULL || Q->back == NULL) return false;
  if (!is_queue_segment(Q->front, Q->back)) return false;
  return true;
}

bool queue_empty(queue *Q) {
  REQUIRES(is_queue(Q));
  return Q->front == Q->back;
}

queue *queue_new() {
  queue *Q = xmalloc(sizeof(queue));
  list *p = xmalloc(sizeof(list));
  /* Dummy node: does not need to be initialized! */
  Q->front = p;
  Q->back = p;

  ENSURES(is_queue(Q));
  ENSURES(queue_empty(Q));
  return Q;
}

void enq(queue *Q, queue_elem x) {
  REQUIRES(is_queue(Q));

  Q->back->data = x;
  Q->back->next = xmalloc(sizeof(list));
  Q->back = Q->back->next;

  ENSURES(is_queue(Q) && !queue_empty(Q));
}

queue_elem deq(queue *Q) {
  REQUIRES(is_queue(Q));
  REQUIRES(!queue_empty(Q));

  queue_elem x = Q->front->data;  /* save old queue element to return */
  list *q = Q->front;             /* save old list node to free */
  Q->front = Q->front->next;
  free(q);                      /* free old list node */

  ENSURES(is_queue(Q));
  return x;                     /* return old queue element */
}

void queue_free(queue *Q) {
  REQUIRES(is_queue(Q));

  while (Q->front != Q->back) {
    ASSERT(is_queue_segment(Q->front, Q->back));
    list *p = Q->front;
    Q->front = Q->front->next;
    free(p);
  }

  free(Q->front); /* == Q->back */
  free(Q);
}
