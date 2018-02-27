/*
 * Graphs - version 2: Adjacency Matrix
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include "graph.h"
#include "lib/xalloc.h"
#include "lib/contracts.h"

typedef struct graph_header graph;
struct graph_header {
  unsigned int size;
  bool **adj;        // Pointer to adjacency matrix
};

/* Data structure invariants */

bool is_vertex(graph *G, vertex v) {
  REQUIRES(G != NULL);
  return v < G->size;
}

bool is_graph(graph *G) {
  if (G == NULL) return false;
  if (G->adj == NULL) return false;
  for (unsigned int i = 0; i < G->size; i++) {
    if (G->adj[i] == NULL) return false;
  }

  // TO BE COMPLETED:





  return true;
}

graph *graph_new(unsigned int size) {
  graph *G = xmalloc(sizeof(graph));
  // TO BE COMPLETED:





  ENSURES(is_graph(G));
  return G;
}

void graph_free(graph *G) {
  REQUIRES(is_graph(G));
  // TO BE COMPLETED:





  free(G);
}

unsigned int graph_size(graph *G) {
  REQUIRES(is_graph(G));
  return G->size;
}

bool graph_hasedge(graph *G, vertex v, vertex w) {
  REQUIRES(is_graph(G) && is_vertex(G, v) && is_vertex(G, w));
  // TO BE COMPLETED:




  return false;
}

void graph_addedge(graph *G, vertex v, vertex w) {
  REQUIRES(is_graph(G) && is_vertex(G, v) && is_vertex(G, w));
  REQUIRES(!graph_hasedge(G, v, w));
  // TO BE COMPLETED:





  ENSURES(is_graph(G));
}
