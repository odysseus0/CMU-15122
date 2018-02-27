/*
 * Binary search tree without balancing
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"
#include "lib/xalloc.h"
#include "lib/contracts.h"

/**************************/
/* Library implementation */
/**************************/

typedef struct tree_node tree;
struct tree_node {
  elem data;
  tree *left;
  tree *right;
};

typedef struct bst_header bst;
struct bst_header {
  tree *root;
  compare_fn *compare;
};

/* is_ordered(T, lower, upper) checks if all elements in T
 * are strictly in the interval (elem_key(lower),elem_key(kupper)).
 * lower = NULL represents -infinity; upper = NULL represents +infinity
 */
bool is_ordered(tree *T, elem lower, elem upper, compare_fn *compare)
{
  REQUIRES(compare != NULL);
  if (T == NULL) return true;
  if (T->data == NULL) return false;
  elem mid = T->data;
  if (!(lower == NULL || (*compare)(lower, mid) < 0))
    return false;
  if (!(upper == NULL || (*compare)(mid, upper) < 0))
    return false;
  return is_ordered(T->left, lower, mid, compare)
    && is_ordered(T->right, mid, upper, compare);
}

bool is_tree(tree *T, compare_fn *compare)
{
  REQUIRES(compare != NULL);
  return is_ordered(T, NULL, NULL, compare);
}

bool is_bst(bst *B) {
  return B != NULL
    && B->compare != NULL
    && is_tree(B->root, B->compare);
}

/* You'll need to add a new parameter to this function
 * (be sure to add it in bst.h as well!) */
bst *bst_new(compare_fn *compare)
//@requires compare != NULL;
//@ensures is_bst(\result);
{
  /* REWRITE ME:
  bst* B = alloc(struct bst_header);
  B->root = NULL;
  B->compare = compare;
  return B;
  */
  // delete the following lines
  (void)compare;
  return NULL;
}

/* tree_insert(T, e, compare) returns the modified tree
 * this avoids some complications in case T = NULL
 */
tree *tree_insert(tree *T, elem e, compare_fn *compare)
{
  REQUIRES(e != NULL && compare != NULL && is_tree(T, compare));
  if (T == NULL) {
    /* create new node and return it */
    T = xmalloc(sizeof(struct tree_node));
    T->data = e;
    T->left = NULL; T->right = NULL;
    ENSURES(is_tree(T, compare));
    return T;
  }
  int r = (*compare)(e, T->data);
  if (r == 0) {
    T->data = e;               /* modify in place */
  } else if (r < 0) {
    T->left = tree_insert(T->left, e, compare);
  } else {
    ASSERT(r > 0);
    T->right = tree_insert(T->right, e, compare);
  }
  ENSURES(is_tree(T, compare));
  return T;
}

void bst_insert(bst *B, elem e)
{
  REQUIRES(is_bst(B) && e != NULL);
  B->root = tree_insert(B->root, e, B->compare);
  ENSURES(is_bst(B));
  return;
}



void bst_free(bst *B)
{
  /* WRITE ME (you'll want to add a helper function called tree_free above)
   * (also, delete the following line) */
  (void)B;
}
