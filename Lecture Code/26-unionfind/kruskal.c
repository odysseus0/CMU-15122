/* Union-find testing via Kruskal's algorithm
 * 15-122 Principles of Imperative Computation, Fall 2010
 * Frank Pfenning
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "unionfind.h"

typedef struct edge_info edge;
struct edge_info {
  int v;
  int u;
  unsigned int weight;
};

unsigned char node_name(int v) {
  return v + 0x61;
}

// pre-sorted edge list
edge* nine_edges() {
  edge* result = xmalloc(9 * sizeof(edge));
  result[0].v = 0;
  result[0].u = 3;
  result[0].weight = 1;

  result[1].v = 4;
  result[1].u = 5;
  result[1].weight = 2;

  result[2].v = 2;
  result[2].u = 4;
  result[2].weight = 3;

  result[3].v = 4;
  result[3].u = 3;
  result[3].weight = 4;

  result[4].v = 3;
  result[4].u = 5;
  result[4].weight = 5;

  result[5].v = 2;
  result[5].u = 3;
  result[5].weight = 5;

  result[6].v = 0;
  result[6].u = 2;
  result[6].weight = 8;

  result[7].v = 0;
  result[7].u = 1;
  result[7].weight = 13;

  result[8].v = 1;
  result[8].u = 2;
  result[8].weight = 15;
  return result;
}

int main () {
  edge *edges = nine_edges();
  //graph_t T = graph_new(6);
  ufs_t eqs = singletons(6);
  size_t num_edges = 0;
  size_t next_edge = 0;
  
  while ( num_edges < 5 && next_edge < 9 ) {
    edge e = edges[next_edge];
    printf("Looking at edge from %c to %c of weight %d\n",
	   node_name(e.v), node_name(e.u), e.weight);
    if (ufs_find(eqs, e.v) != ufs_find(eqs, e.u) ) {
      printf("Adding edge from %c to %c\n", node_name(e.v), node_name(e.u));
      ufs_union(eqs, e.v, e.u);
      assert(ufs_find(eqs, e.v) == ufs_find(eqs, e.u));
      //graph_addedge(T, e.v, e.u, e.weight);
      num_edges++;
    }
    next_edge++;
  }
  printf("Checking that all nodes are in same equivalence class.\n");
  for (int i = 0; i < 6-1; i++)
    assert(ufs_find(eqs,i) == ufs_find(eqs,i+1)); // a spanning tree?
  ufs_free(eqs);

  printf("All tests passed!\n");
  return 0;
}
