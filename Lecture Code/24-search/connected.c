/*
 * Graph search
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdbool.h>
#include <stdio.h>
#include "lib/graph.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "lib/queue.h"
#include "lib/stack.h"


bool naive_dfs(graph_t G, vertex start, vertex target) {
  REQUIRES(G != NULL);
  REQUIRES(start < graph_size(G) && target < graph_size(G));
  printf("    Visiting %u\n", start);

  // there is a path from start to target if
  // target == start, or
  if (target == start) return true;
  // there is an edge from start to v ...
  for (vertex v=0 ; v < graph_size(G) ; v++) {
    if (graph_hasedge(G, start, v)) { // This v is one of start's neighbors
      // ... and a path from v to target
      if (naive_dfs(G, v, target)) return true;
    }
  }
  return false;
}

bool dfs_helper(graph_t G, bool *mark, vertex start, vertex target) {
  REQUIRES(G != NULL && mark != NULL);
  REQUIRES(start < graph_size(G) && target < graph_size(G));
  REQUIRES(!mark[start]);

  // mark start as seen
  mark[start] = true;
  printf("    Visiting %u\n", start);

  // there is an edge from start to v and a path from v to target if...
  // target == start, or
  if (target == start) return true;
  // there is an edge from start to v ...
  for (vertex v=0 ; v < graph_size(G) ; v++) {
    if (graph_hasedge(G, start, v)) { // This v is one of start's neighbors
      // ... and a path from v to target
      if (!mark[v] && dfs_helper(G, mark, v, target))
        return true;
    }
  }

  return false;
}

bool dfs(graph_t G, vertex start, vertex target) {
  REQUIRES(G != NULL);
  REQUIRES(start < graph_size(G) && target < graph_size(G));

  bool mark[graph_size(G)];
  for (vertex i = 0; i < graph_size(G); i++)
    mark[i] = false;
  return dfs_helper(G, mark, start, target);
}

bool bfs(graph_t G, vertex start, vertex target) {
  REQUIRES(G != NULL);
  REQUIRES(start < graph_size(G) && target < graph_size(G));

  if (start == target) return true;

  // mark is an array containing only the start
  bool mark[graph_size(G)];
  for (vertex i = 0; i < graph_size(G); i++)
    mark[i] = false;

  // Q initially is a queue containing only the start
  queue_t Q = queue_new();
  enq(Q, start);
  mark[start] = true;

  while (!queue_empty(Q)) {
    // LI 1: every marked vertex is connected to start
    // LI 2: every vertex in Q is marked
    // LI 3: Every path from start to target goes through a vertex in Q

    // Find a node v that we haven't looked at yet
    vertex v = deq(Q);
    printf("    Visiting %u\n", v);
    //   for (every vertex w adjacent to v) {
    for (vertex w=0 ; w < graph_size(G) ; w++) {
      if (graph_hasedge(G, v, w)) {
        if (w == target) {  // if w is the target return true
          printf("    Found    %u !!!\n", w);
          queue_free(Q);
          return true;
        }

        if (!mark[w]) {     // if w is not already marked
          mark[w] = true;      // Insert it into the marks
          enq(Q, w);           // Enqueue it onto the queue
        }
      }
    }
  }
  queue_free(Q);
  return false;
}

// Exercise: write iterative dfs by modifying the bfs code
// replacing the queue with a stack.

bool dfs_explicit_stack(graph_t G, vertex start, vertex target) {
  REQUIRES(G != NULL);
  REQUIRES(start < graph_size(G) && target < graph_size(G));
  REQUIRES(start < graph_size(G) && target < graph_size(G));

  return false;
}
