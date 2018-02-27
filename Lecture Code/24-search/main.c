/*
 * Graph search
 *
 * 15-122 Principles of Imperative Computation
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/graph.h"

// function prototypes
bool naive_dfs(graph_t G, vertex start, vertex target);
bool dfs(graph_t G, vertex start, vertex target);
bool bfs(graph_t G, vertex start, vertex target);
bool dfs_explicit_stack(graph_t G, vertex start, vertex target);

/* connected 5 - from lecture notes

     0       3
     | \     |
     |   4   |
     | /   \ |
     1-------2
*/
void print_connected5() {
  printf("\n");
  printf("con5:\n");
  printf("     0       3\n"
         "     | \\     |\n"
         "     |   4   |\n"
         "     | /   \\ |\n"
         "     1-------2\n");
}
graph_t connected5() {
  graph_t G = graph_new(5);
  graph_addedge(G, 0, 1);
  graph_addedge(G, 1, 2);
  graph_addedge(G, 2, 3);
  graph_addedge(G, 0, 4);
  graph_addedge(G, 1, 4);
  graph_addedge(G, 2, 4);
  return G;
}

/* connected6

     0   1---2
     |   |
     3---4   5
*/
void print_connected6() {
  printf("\n");
  printf("con6:\n");
  printf("     0   1---2\n"
         "     |   |    \n"
         "     3---4   5\n");
}
graph_t connected6() {
  graph_t G = graph_new(6);
  graph_addedge(G, 0, 3);
  graph_addedge(G, 3, 4);
  graph_addedge(G, 4, 1);
  graph_addedge(G, 1, 2);
  return G;
}


/* disconnected15

     0---1---2---3   4
     |           |   |
     5   6---7   8   9
     |           |   |
    10--11--12  13  14
*/
void print_disconnected15() {
  printf("\n");
  printf("discon15:\n");
  printf("     0---1---2---3   4\n"
         "     |           |   |\n"
         "     5   6---7   8   9\n"
         "     |           |   |\n"
         "    10--11--12  13  14\n");
}
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

     0---1---2---3   4
     |           |   |
     5   6---7---8   9
     |           |   |
    10--11--12  13--14
*/
void print_connected15() {
  printf("\n");
  printf("con15:\n");
  printf("     0---1---2---3   4\n"
         "     |           |   |\n"
         "     5   6---7---8   9\n"
         "     |           |   |\n"
         "    10--11--12  13--14\n");
}
graph_t connected15() {
  graph_t G = disconnected15();
  graph_addedge(G, 7, 8);
  graph_addedge(G, 13, 14);
  return G;
}


typedef bool graph_search_fn(graph_t G, vertex start, vertex target);

void test(graph_t G, char *graph,
         vertex start, vertex target,
         graph_search_fn *f, char *algo) {
  printf("\n");
  printf("Searching with %s for a path in %s from %u to %u...\n",
         algo, graph, start, target);
  printf("%s\n", (*f)(G, start, target) ? "Reachable" : "UNREACHABLE");
  printf("\n");
}

void print_synopsys(char *cmd) {
    printf("\n");
    printf("SYNOPSIS\n");
    printf("\n");
    printf("  %s <algo> <graph> <start> <target>\n", cmd);
    printf("      Searches for a path from <start> to <target>\n");
    printf("      in graph <graph> using algorithm <algo>\n");
    printf("\n");
    printf("  Valid <algo>: 'naive_dfs', 'dfs', 'bfs', 'dfs_explicit_stack'\n");
    //printf("  Valid <graph>: 'con5', 'con6', 'con15', 'discon15'\n");
    printf("  Valid <graph>:\n");
    print_connected5();
    print_connected6();
    print_connected15();
    print_disconnected15();
    printf("\n");
}

int main(int argc, char **argv) {

  if (argc == 5) {
    graph_search_fn *f;
    char *algo;
    if (strcmp(argv[1], "naive_dfs") == 0) {
      f = &naive_dfs;
      algo = "naive DFS";
    } else if (strcmp(argv[1], "dfs") == 0) {
      f = &dfs;
      algo = "DFS (recursive)";
    } else if (strcmp(argv[1], "bfs") == 0) {
      f = &bfs;
      algo = "BFS";
    } else if (strcmp(argv[1], "dfs_explicit_stack") == 0) {
      f = &dfs_explicit_stack;
      algo = "DFS (explicit stack)";
    } else {
      printf("Unknown algorithm %s\n", argv[1]);
      exit(1);
    }

    graph_t G;
    if (strcmp(argv[2], "con5") == 0) {
      print_connected5();
      G = connected5();
    } else if (strcmp(argv[2], "con6") == 0) {
      print_connected6();
      G = connected6();
    }
    else if (strcmp(argv[2], "discon15") == 0) {
      print_disconnected15();
      G = disconnected15();
    }
    else if (strcmp(argv[2], "con15") == 0) {
      print_connected15();
      G = connected15();
    }
    else {
      printf("Unknown graph %s\n", argv[2]);
      exit(1);
    }

    vertex start  = atoi(argv[3]);
    vertex target = atoi(argv[4]);

    test(G, argv[2], start, target, f, algo);
    graph_free(G);
  }

  else print_synopsys(argv[0]);

  // Interesting tests:
  // a.out naive_dfs con5   3  0
  // a.out naive_dfs con5   0  3  // Diverges
  // a.out naive_dfs con6   5  0
  // a.out naive_dfs con6   0  5  // Diverges
  // a.out naive_dfs con15 12  0
  // a.out naive_dfs con15  8 12  // Diverges

  // a.out dfs con5   3  0
  // a.out dfs con5   0  3  // Diverges
  // a.out dfs con6   5  0
  // a.out dfs con6   0  5  // Diverges
  // a.out dfs con15 12  0
  // a.out dfs con15  8 12  // Diverges

  // a.out bfs con5   3  0
  // a.out bfs con5   0  3  // Diverges
  // a.out bfs con6   5  0
  // a.out bfs con6   0  5  // Diverges
  // a.out bfs con15 12  0
  // a.out bfs con15  8 12  // Diverges

}
