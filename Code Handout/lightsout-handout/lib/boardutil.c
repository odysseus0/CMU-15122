/* 
 * Board utilities
 *
 * 15-122 Principles of Imperative Computation 
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "contracts.h"
#include "bitvector.h"
#include "boardutil.h"

/* Valid board dimensions */
bool is_valid_boardsize(uint8_t width, uint8_t height) {
  if (width == 0) return false;
  if (height == 0) return false;
  if (!(width <= UINT8_MAX / height)) return false;
  if (!(width*height <= BITVECTOR_LIMIT)) return false;
  return true;
}

/* Valid board positions */
bool is_valid_pos(int row, int col, uint8_t width, uint8_t height) {
  REQUIRES(is_valid_boardsize(width, height));

  int w = (unsigned int) width;
  int h = (unsigned int) height;
  
  if (row < 0) return false;
  if (row >= h) return false;
  if (col < 0) return false;
  if (col >= w) return false;

  return true;
}

/* Read from a file, but ignore whitespace */
static inline int read_non_space(FILE *F) {
  int c;
  do c = fgetc(F);
  while (isspace(c));
  return c;
}

/* Interprets a char as a digit, returns -1 if it isn't one */
static inline int digit(int c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  return -1;
}

/* Reads the width, height, and bitvector out of a file */
/* Returns true if successful, false otherwise */
bool file_read(char *path, 
               bitvector *vec_out,
               uint8_t *width_out,
               uint8_t *height_out) {
  REQUIRES(path != NULL);
  REQUIRES(vec_out != NULL && width_out != NULL && height_out != NULL);
  
  bitvector board = bitvector_new();

  /* Open a file for reading */
  FILE *F = fopen(path, "r");
  if (F == NULL) {
    fprintf(stderr, "file_read: unable to open file %s", path);
    return false;
  }
  
  /* Read width x height from file, return 'false' if invalid */
  int width = digit(read_non_space(F));

  if (width <= 0) { 
    fprintf(stderr, "file_read: bad width in file %s", path);
    fclose(F); 
    return false; 
  }

  if (read_non_space(F) != 'x') {
    fprintf(stderr, "file_read: invalid size spec in %s", path);
    fclose(F); 
    return false;
  }

  int height = digit(read_non_space(F));
  if (height <= 0) { 
    fprintf(stderr, "file_read: bad height in file %s", path);
    fclose(F); 
    return false; 
  }

  /* Board too big for this implementation of bitvectors */
  if (width * height > BITVECTOR_LIMIT) {
    fprintf(stderr, "file_read: board in %s is too big", path);
    fclose(F); 
    return false; 
  }

  /* Read the board contents, toggle all the '#' spaces. */
  for (int i = 0; i < width * height; i++) {
    int c = read_non_space(F);
    if (c == '#') board = bitvector_flip(board, i);
    else if (c != 'O') { 
      if (c == EOF) {
        fprintf(stderr, "file_read: board in %s is smaller than spec", path);
      } else { 
        fprintf(stderr, "file_read: invalid character %c in %s", c, path);
      }
      fclose(F); 
      return false; 
    }
  }

  // Check that we're at the end of the file
  int c = read_non_space(F);
  fclose(F);
  if (EOF != c) {
    fprintf(stderr, "file_read: board in %s is larger than spec", path);
    return false;
  } 
 
  ENSURES(is_valid_boardsize(width, height));
  *width_out = (uint8_t)width;
  *height_out = (uint8_t)height;
  *vec_out = board;
  return true;
}

void print_board(bitvector vec, uint8_t width, uint8_t height) {
  REQUIRES(is_valid_boardsize(width, height));
  
  for (uint8_t row = 0; row < height; row++) {
    for (uint8_t col = 0; col < width; col++) {
      int i = row * width + col;
      if (bitvector_get(vec, i)) fprintf(stderr, "#");
      else fprintf(stderr, "O");
    }
    fprintf(stderr, "\n");
  }
}

/* Index lookup */
uint8_t get_index(int row, int col, uint8_t width, uint8_t height) {
  REQUIRES(is_valid_boardsize(width, height));
  REQUIRES(is_valid_pos(row, col, width, height));

  uint8_t r = row;
  uint8_t c = col;
  (void) height;

  return r*width + c;
}
