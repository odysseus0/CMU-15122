/*
 * Graph Search
 *
 * 15-122 Principles of Imperative Computation
 * Tom Cortina
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graph-search.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"

/* disconnected6
   |---|---|---|
   | 0 | 1   2 |
   |   |   |---|
   | 3   4 | 5 |
   |---|---|---| */

graph_t disconnected6() {
  graph_t G = graph_new(6);
  graph_addedge(G, 0, 3);
  graph_addedge(G, 3, 4);
  graph_addedge(G, 4, 1);
  graph_addedge(G, 1, 2);
  return G;
}


/* disconnected15

   |---|---|---|---|---|
   | 0   1   2   3 | 4 |
   |   |---|---|   |   |
   | 5 | 6   7 | 8 | 9 |
   |   |---|---|   |   |
   | A   B   C | D | E |
   |---|---|---|---|---| */

graph_t disconnected15() {
  graph_t G = graph_new(15);
  graph_addedge(G, 0, 1);
  assert(graph_hasedge(G, 0, 1));
  assert(graph_hasedge(G, 1, 0));

  graph_addedge(G, 1, 2);
  assert(graph_hasedge(G, 0, 1));
  assert(graph_hasedge(G, 1, 0));
  assert(graph_hasedge(G, 1, 2));
  assert(graph_hasedge(G, 2, 1));

  graph_addedge(G, 2, 3);
  graph_addedge(G, 6, 7);
  graph_addedge(G, 10, 11);
  graph_addedge(G, 11, 12);

  graph_addedge(G, 0, 5);
  graph_addedge(G, 5, 10);
  graph_addedge(G, 8, 13);
  graph_addedge(G, 3, 8);
  graph_addedge(G, 4, 9);
  graph_addedge(G, 9, 14);

  return G;
}

/* connected15

   |---|---|---|---|---|
   | 0   1   2   3 | 4 |
   |   |---|---|   |   |
   | 5 | 6   7   8 | 9 |
   |   |---|---|   |   |
   | A   B   C | D   E |
   |---|---|---|---|---| */

graph_t connected15() {
  graph_t G = disconnected15();
  graph_addedge(G, 7, 8);
  graph_addedge(G, 13, 14);
  return G;
}

int main() {
  char *pass = "Test passed!";
  char *fail = "*******************\n*** TEST FAILED ***\n*******************";

  graph_t maze6 = disconnected6();

  printf("Searching disconnected6 using DFS for a path from 0 to 2...\n");
  bool mark6[6];
  for (vertex i = 0; i < 6; i++) mark6[i] = false;
  printf("%s\n", dfs(maze6, mark6, 0, 2) ? pass : fail);

  printf("Searching disconnected6 using BFS for a path from 0 to 2...\n");
  printf("%s\n", bfs(maze6, 0, 2) ? pass : fail);

  printf("Searching disconnected6 using DFS for a path from 3 to 5...\n");
  for (vertex i = 0; i < 6; i++) mark6[i] = false;
  printf("%s\n", dfs(maze6, mark6, 3, 5) ? fail : pass);

  printf("Searching disconnected6 using BFS for a path from 3 to 5...\n");
  printf("%s\n", bfs(maze6, 3, 5) ? fail : pass);

  graph_t maze15d = disconnected15();
  graph_t maze15c = connected15();

  printf("Searching disconnected15 with DFS for a path from 7 to 12...\n");
  bool mark15[15];
  for (vertex i = 0; i < 15; i++) mark15[i] = false;
  printf("%s\n", dfs(maze15d, mark15, 7, 12) ? fail : pass);

  printf("Searching disconnected15 with BFS for a path from 7 to 12...\n");
  printf("%s\n", bfs(maze15d, 7, 12) ? fail : pass);

  printf("Searching connected15 with DFS for a path from 7 to 12...\n");
  for (vertex i = 0; i < 15; i++) mark15[i] = false;
  printf("%s\n", dfs(maze15c, mark15, 7, 12) ? pass : fail);

  printf("Searching connected15 with BFS for a path from 7 to 12...\n");
  printf("%s\n", bfs(maze15c, 7, 12) ? pass : fail);

  graph_free(maze6);
  graph_free(maze15d);
  graph_free(maze15c);

  return 0;
}
