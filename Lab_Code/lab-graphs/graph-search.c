/*
 * Graph Search - version 2: with adjacency matrix
 *
 * 15-122 Principles of Imperative Computation
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graph-search.h"
#include "lib/contracts.h"
#include "lib/queue.h"
#include "lib/stack.h"
#include "lib/xalloc.h"

/* DFS Search using system stack (i.e. recursive) */

bool dfs(graph_t G, bool *mark, vertex start, vertex target) {
  REQUIRES(mark != NULL);
  REQUIRES(start < graph_size(G) && target < graph_size(G));

  if (mark[start]) return false;
  mark[start] = true;

  printf("DFS visiting %d\n", start);
  if(start == target) return true;

  for (unsigned int i = 0; i < graph_size(G); i++) {
    if (graph_hasedge(G, start, i)) {
      if (i == target) return true;
      if (dfs(G, mark, i, target)) return true;
    }
  }

  return false;
}

/* BFS Search using queue */

bool bfs(graph_t G, vertex start, vertex target) {
  REQUIRES(start < graph_size(G) && target < graph_size(G));
  REQUIRES(start < graph_size(G) && target < graph_size(G));

  if (start == target) return true;

  bool mark[graph_size(G)];
  for (unsigned int i = 0; i < graph_size(G); i++) 
    mark[i] = false;
  mark[start] = true;

  queue_t Q = queue_new();
  enq(Q, start);

  while(!queue_empty(Q)) {
    vertex v = deq(Q);
    for (vertex w = 0; w < graph_size(G); w++) {
      if (graph_hasedge(G, v, w)) {
        printf("BFS visiting %d\n", w);
        if (w == target) {
          queue_free(Q);
          return true;
        } else if (!mark[w]) {
          mark[w] = true;
          enq(Q, w);
        }
      }
    }
  }

  queue_free(Q);
  return false;
}

