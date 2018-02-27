/*
 * Graphs
 *
 * 15-122 Principles of Imperative Computation
 * Rob Simmons and Tom Cortina
 */

#include <stdbool.h>
#include <inttypes.h>

#ifndef _GRAPH_H
#define _GRAPH_H

typedef unsigned int vertex;
typedef struct graph_header* graph_t;

// New graph with numvert vertices
graph_t graph_new(unsigned int numvert);
  //@ensures \result != NULL;

unsigned int graph_size(graph_t G);
  //@requires G != NULL;
 
bool graph_hasedge(graph_t G, vertex v, vertex w);
  //@requires G != NULL;
  //@requires v < graph_size(G) && w < graph_size(G);

void graph_addedge(graph_t G, vertex v, vertex w);
  //@requires G != NULL;
  //@requires v != w && v < graph_size(G) && w < graph_size(G);
  //@requires !graph_hasedge(G, v, w);

void graph_free(graph_t G);
  //@requires G != NULL;

#endif


