/* 
 * Hash tables wrapper 
 *
 * 15-122 Principles of Imperative Computation */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "lib/bitvector.h"
#include "lib/hdict.h"

#ifndef _BOARD_HASHTABLE_H_
#define _BOARD_HASHTABLE_H_

struct board_data {
  // Ignore this field (but don't remove it or change its type)
  uint8_t test;

  // This part of the struct acts like the key
  bitvector board;

  // You can add more fields to this struct
  // in order to help you implement the later tasks.
};

/* IMPORTANT: You must respect the hash set interface in hdict.h when
 * writing your implementation of these functions! */

/* Initializes a new hash table with the given capacity */
hdict_t ht_new(size_t capacity)
  /*@requires capacity > 0; @*/
  /*@ensures \result != NULL; @*/ ;

/* ht_lookup(H,B) returns 
 * NULL if no struct containing the board B exists in H
 * A struct containing the board B if one exists in H.
 */
struct board_data *ht_lookup(hdict_t H, bitvector B)
  /*@requires H != NULL; @*/ ;

/* ht_insert(H,e) has no return value, because it should have as
 * a precondition that no struct currently in the hashtable contains
 * the same board as DAT->board.
 */
void ht_insert(hdict_t H, struct board_data *DAT)
  /*@requires H != NULL; @*/ ;

#endif
