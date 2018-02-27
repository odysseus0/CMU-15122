#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/xalloc.h"

/*************************************/
/*************************************/
/*** Adapted from Lecture 15 (BST) ***/
/*************************************/
/*************************************/

/***** Look for the string "NEW" *****/

/***************/
/* Client Code */
/***************/

typedef void* entry;
typedef void* key;

key entry_key(entry e) {
  return e;
}
int key_compare(key k1, key k2)
//@requires \hastag(int*, k1) && \hastag(int*, k2);
{
  if (*(int*)k1 < *(int*)k2) return -1;
  if (*(int*)k1 > *(int*)k2) return 1;
  return 0;
}

/************************************/
/* Client-side Dictionary interface */
/************************************/

// typedef ______* entry;        // Supplied by client
// typedef ______  key;          // Supplied by client

key entry_key(entry e)           // Supplied by client
/*@requires e != NULL; @*/ ;

int key_compare(key k1, key k2)  // Supplied by client
/*@ensures -1 <= \result && \result <= 1; @*/ ;

/************************************************/
/* Dictionary Library implementation using BSTs */
/************************************************/

/* BSTs and auxiliary functions */
typedef struct tree_node tree;
struct tree_node {
  entry data;  // != NULL
  tree* left;
  tree* right;
};

/* Minimal tree representation check */
bool is_tree(tree* T) { // minimal
  // Code for empty tree
  if (T == NULL) return true;

  // Code for non-empty tree
  return T->data != NULL
      && is_tree(T->left)
      && is_tree(T->right);
}

/* is_ordered(T, lo, hi) checks if all entries in T
 * are strictly in the interval (lo,hi).
 * lo = NULL represents -infinity; hi = NULL represents +infinity */
bool is_ordered(tree* T, entry lo, entry hi)
//@requires is_tree(T);
{
  // Code for empty tree
  if (T == NULL) return true;

  // Code for non-empty tree
  return T->data != NULL
      && (lo == NULL || key_compare(entry_key(lo), entry_key(T->data)) < 0)
      && (hi == NULL || key_compare(entry_key(T->data), entry_key(hi)) < 0)
      && is_ordered(T->left, lo, T->data)
      && is_ordered(T->right, T->data, hi);
}

bool is_bst(tree* T) { // minimal
  return is_tree(T)
      && is_ordered(T, NULL, NULL);
}

entry bst_lookup(tree* T, key k)
//@requires is_bst(T);
//@ensures \result == NULL || key_compare(entry_key(\result), k) == 0;
{
  // Code for empty tree
  if (T == NULL) return NULL;

  // Code for non-empty tree
  int cmp = key_compare(k, entry_key(T->data));
  if (cmp == 0)  return T->data;
  if (cmp <  0)  return bst_lookup(T->left, k);
  //@assert cmp > 0;
  return bst_lookup(T->right, k);
}
tree* bst_insert(tree* T, entry e)
//@requires is_bst(T) && e != NULL;
//@ensures is_bst(\result) && bst_lookup(T, entry_key(e)) != NULL;
{
  // Code for empty tree
  if (T == NULL) {
    tree* R  = xmalloc(sizeof(tree));
    R->data  = e;
    R->left  = NULL;
    R->right = NULL;
    return R;
  }

  // Code for non-empty tree
  int cmp = key_compare(entry_key(e), entry_key(T->data));
  if (cmp == 0)     T->data = e;
  else if (cmp < 0) T->left = bst_insert(T->left, e);
  else {
    //@assert cmp > 0;
    T->right = bst_insert(T->right, e);
  }

  return T;
}

/******* Implementing the dictionaries ******/

struct dict_header {
  tree* root;
};
typedef struct dict_header dict;

bool is_dict(dict* D) {
  return D != NULL && is_bst(D->root);
}

dict* dict_new()
//@ensures is_dict(\result);
{
  dict* D = xmalloc(sizeof(dict));
  D->root = NULL;
  return D;
}

entry dict_lookup(dict* D, key k)
//@requires is_dict(D);
//@ensures \result == NULL || key_compare(entry_key(\result), k) == 0;
{
  return bst_lookup(D->root, k);
}

void dict_insert(dict* D, entry e)
//@requires is_dict(D) && e != NULL;
//@ensures is_dict(D) && dict_lookup(D, entry_key(e)) != NULL;
{
  D->root = bst_insert(D->root, e);
}


/****** NEW: Free functions *******/

typedef void elem_free_fn(void* x);

void tree_free(tree *T, elem_free_fn *Fr) {
  // REQUIRES(is_ordtree(T));
  if (T == NULL) return;

  if (Fr != NULL) (*Fr)(T->data);
  tree_free(T->left, Fr);
  tree_free(T->right, Fr);
  free(T);
}

void dict_free(dict *D, elem_free_fn *Fr) {
  //REQUIRES(is_bst(D));
  tree_free(D->root, Fr);
  free(D);
}



typedef dict* dict_t;


/*********************/
/* Library interface */
/*********************/

// typedef ______* dict_t;

dict_t dict_new()
/*@ensures \result != NULL; @*/ ;

entry dict_lookup(dict_t D, key k)
/*@requires D != NULL; @*/
/*@ensures \result == NULL || key_compare(entry_key(\result), k) == 0; @*/ ;

void dict_insert(dict_t D, entry e)
/*@requires D != NULL && e != NULL; @*/
/*@ensures D != NULL && dict_lookup(D, entry_key(e)) != NULL; @*/ ;

/****** NEW *******/
void dict_free(dict_t D, elem_free_fn *Fr)
/*@requires D != NULL; @*/ ;


int* mk_int(int x) {
  int *p = xmalloc(sizeof(int));
  *p = x;
  return p;
}

int main() {
  dict_t D = dict_new();
  dict_insert(D, (void*)mk_int(0));
  dict_insert(D, (void*)mk_int(12));
  dict_insert(D, (void*)mk_int(37));
  dict_insert(D, (void*)mk_int(-42));

  dict_free(D, free);
}
