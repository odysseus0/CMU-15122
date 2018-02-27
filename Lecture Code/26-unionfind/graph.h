/*
 * Graphs
 *
 * 15-122 Principles of Imperative Computation, Fall 2012
 * Rob Simmons
 */

#include <stdbool.h>
#include <inttypes.h>

#ifndef _GRAPH_H
#define _GRAPH_H

typedef unsigned int vertex;
typedef struct graph_header* graph_t;

graph_t graph_new(unsigned int numvert); // New graph with numvert vertices
void graph_free(graph_t G);
unsigned int graph_size(graph_t G);  // Number of vertices in the graph

bool graph_hasedge(graph_t G, vertex v, vertex w);
  //@requires v < graph_size(G) && w < graph_size(G);

void graph_addedge(graph_t G, vertex v, vertex w); // Edge can't be in graph!
  //@requires v < graph_size(G) && w < graph_size(G);
  //@requires v != w && !graph_hasedge(G, v, w);

#endif


