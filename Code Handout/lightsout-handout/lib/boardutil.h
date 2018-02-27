/* 
 * Board utilities
 *
 * 15-122 Principles of Imperative Computation  */

#include <stdbool.h>
#include <stdint.h>
#include "bitvector.h"

#ifndef _BOARDUTIL_H_
#define _BOARDUTIL_H_

/* Check whether a width and height ar valid boards, 
 * representable as bit vectors */
bool is_valid_boardsize(uint8_t width, uint8_t height);

/* Check whether row and column are valid boards for the given width
 * and height
 */
bool is_valid_pos(int row, int col, uint8_t width, uint8_t height)
  /*@requires is_valid_boardsize(width, height); @*/ ;

/* Get the index for a position (standard row-major ordering used in
 * the image and peg solitaire assignments)
 */
uint8_t get_index(int row, int col, uint8_t width, uint8_t height)
  /*@requires is_valid_boardsize(width, height); @*/ 
  /*@requires is_valid_pos(row, col, width, height); @*/ ;

/* Tries to read a lightboard from the file 'path'
 * Failure: returns false
 * Success: writes the vector of bits into 'vec_out'
 *          writes the width into 'width_out'
 *          writes the height into 'height_out'
 * 
 * Requires: All non-NULL pointers, path must be a string
 * Ensures: !\result || is_valid_boardsize(*width_out, *height_out) */
bool file_read(char *path, 
               bitvector *vec_out,
               uint8_t *width_out,
               uint8_t *height_out)
  /*@requires path != NULL && vec_out != NULL; @*/ 
  /*@requires width_out != NULL && height_out != NULL; @*/ 
  /*@ensures !\result || is_valid_boardsize(*width_out, *height_out); @*/ ;

/* Prints a representation of the board to standard error
 */
void print_board(bitvector vec, uint8_t width, uint8_t height)
  /*@requires is_valid_boardsize(width, height); @*/ ;

#endif
