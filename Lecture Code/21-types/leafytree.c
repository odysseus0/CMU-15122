#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"

#define PI 3.14159265

typedef struct ltree leafytree;

/*
// Wastes memory: data for inner node, left and right for leaf, all 3 for empty tree
struct ltree {
  unsigned leafcount;
  int nodetype;  // But 2 bits are enough!
  int data;
  leafytree *left;
  leafytree *right;
};
*/

enum nodetype { INNER, LEAF, EMPTY };

struct innernode {          // inner node: left and right subtrees
  leafytree *left;
  leafytree *right;
};
union nodecontent {         // contents of a non-empty node:
  int data;                 // EITHER an int
  struct innernode node;    //     OR and inner node
};
struct ltree {
  unsigned int leafcount;
  enum nodetype type;
  union nodecontent content;
};

bool is_tree(leafytree *T) {
  if (T == NULL) return false;

  switch (T->type) {
  case EMPTY:
    return T->leafcount == 0;
    // No need for break since we return

  case LEAF:
    return T->leafcount == 1;

  case INNER:
    (void)0;   // Empty statement to make the compiler happy
    leafytree *L = T->content.node.left;
    leafytree *R = T->content.node.right;
    return is_tree(L) && is_tree(R)
        && T->leafcount == L->leafcount + R->leafcount;

  default:  // Not needed, but makes the compiler happy
    return false;
  }
}

leafytree *mk_empty() { // Make an empty node
  leafytree *T = xmalloc(sizeof(leafytree));
  T->type = EMPTY;
  T->leafcount = 0;
  ASSERT(is_tree(T));
  return T;
}
leafytree *mk_leaf(int data) { // Make a leaf node
  leafytree *T = malloc(sizeof(leafytree));
  T->type = LEAF;
  T->leafcount = 1;
  T->content.data = data;
  ASSERT(is_tree(T));
  return T;
}
// Make an inner node
leafytree *mk_inner(leafytree *T_left, leafytree *T_right) {
  ASSERT(is_tree(T_left) && is_tree(T_right));
  leafytree *T = malloc(sizeof(leafytree));
  T->type = INNER;
  T->leafcount = T_left->leafcount + T_right->leafcount;
  T->content.node.left  = T_left;
  T->content.node.right = T_right;
  ASSERT(is_tree(T));
  return T;
}

// Add all the data in a tree
int add_tree(leafytree *T) {
  ASSERT(is_tree(T));
  int n = 0;
  switch (T->type) {
  case INNER:
    n += add_tree(T->content.node.left);
    n += add_tree(T->content.node.right);
    break;

  case LEAF:
    n = T->content.data;
    break;

  default:
    n = 0;
  }

  return n;
}


int main () {

  // Floats
  float x = 0.1;

  for (float res = 0; res <= 5.0; ) {
//  for (float res = 0; res != 5.0; ) { // won't work!
    res += x;
    printf("res = %f\n", res);
  }
  printf("sin pi = %e\n", sin(PI));    // Should be 0.0!


  // Enums, unions, and switch
  leafytree *T0 = mk_empty();
  leafytree *T1 = mk_leaf(42);
  leafytree *T2 = mk_inner(T0, T1);
  printf("add_tree(T) = %d\n", add_tree(T2));

  printf("\n");
}
