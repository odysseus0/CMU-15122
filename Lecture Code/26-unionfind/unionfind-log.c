/*
 * Union-Find
 * No path compression, but height tracking keeps all operations in O(log n)
 * 
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include "unionfind.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"

typedef struct ufs_header ufs;
struct ufs_header {
  int size;
  int *data;
};

/* ufs_elem(eqs, i) if i is a valid element in eqs */
bool ufs_elem(ufs *eqs, int i) {
  return eqs != NULL
    && (0 <= i && i < eqs->size);
}

/* ufs_rep(eqs, i) if i is the representative of an equivalence class */
bool ufs_rep(ufs *eqs, int i) {
  return ufs_elem(eqs, i) 
    && eqs->data[i] < 0;
}

bool is_ufs (ufs *eqs) {
  if (eqs == NULL) return false;
  if (eqs->size < 0) return false;
  if (eqs->data == NULL) return false;
  //@assert eqs->size == \length(eqs->data);
  for (int i = 0; i < eqs->size; i++)
    if (!(ufs_elem(eqs, eqs->data[i]) || ufs_rep(eqs, i)))
      return false;
  return true;
}

/* singletons(n) returns an eqs where each node
 * [0..n) is in its own equivalence class
 */
ufs* singletons(unsigned int n) {
  ufs *eqs = xmalloc(sizeof(ufs));
  eqs->data = xcalloc(n, sizeof(int));

  for (unsigned int i = 0; i < n; i++)
    eqs->data[i] = -1;
  eqs->size = n;

  ENSURES(is_ufs(eqs));
  return eqs;
}

bool is_equiv(ufs *eqs, int i, int j) {
  REQUIRES(is_ufs(eqs));
  REQUIRES(ufs_elem(eqs, i));
  REQUIRES(ufs_elem(eqs, j));

  int i2 = i;
  int j2 = j;
  while (eqs->data[i2] >= 0) i2 = eqs->data[i2];
  while (eqs->data[j2] >= 0) j2 = eqs->data[j2];
  return i2 == j2;
}

/* ufs_find(eqs, i) finds the representative of the
 * equivalence class of i
 */
int ufs_find(ufs *eqs, int i) {
  REQUIRES(is_ufs(eqs));
  REQUIRES(ufs_elem(eqs, i));

  int j = i;
  while (eqs->data[j] >= 0) {
    ASSERT(is_equiv(eqs, i, j));
    j = eqs->data[j];
  }

  ASSERT(is_equiv(eqs, i, j));
  ASSERT(ufs_rep(eqs, j));

  /* eqs->data[i] = j; weak path compression */
  /* strong compression would redirect all intermediate notes to j */

  ENSURES(is_ufs(eqs));
  ENSURES(ufs_rep(eqs, j));
  return j;
}

/* ufs_union(eqs, i, k) takes the union of equivalence
 * classes of i and k
 */
void ufs_union(ufs *eqs, int i, int k) {
  REQUIRES(is_ufs(eqs));

  int *A = eqs->data;
  int irep = ufs_find(eqs, i);
  int krep = ufs_find(eqs, k);
  if (irep == krep) return;
  if (A[irep] < A[krep]) {         /* i has greater depth */
    A[krep] = irep;
  } else if (A[krep] < A[irep]) {  /* k has greater depth */
    A[irep] = krep;
  } else {
    A[krep] = irep;                /* direction is arbitrary */
    A[irep]--;                     /* depth increases by 1 */
  }

  ENSURES(is_ufs(eqs));
  ENSURES(is_equiv(eqs, i, k));
  return;
}

void ufs_free(ufs *eqs) {
  REQUIRES(is_ufs(eqs));
  free(eqs->data);
  free(eqs);
}
