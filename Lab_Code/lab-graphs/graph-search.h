/*
 * Graph Search - version 2: with adjacency matrix
 *
 * 15-122 Principles of Imperative Computation
 * Tom Cortina
 */

#include <stdbool.h>
#include "graph.h"

#ifndef _GRAPH_SEARCH_H
#define _GRAPH_SEARCH_H

bool dfs(graph_t G, bool *mark, vertex start, vertex target);
//@requires mark != NULL;
//@requires start < graph_size(G) && target < graph_size(G);

bool bfs(graph_t G, vertex start, vertex target);
//@requires start < graph_size(G) && target < graph_size(G);
//@requires start < graph_size(G) && target < graph_size(G);

#endif
