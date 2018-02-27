#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "c0vm.h"
#include "xalloc.h"
#include "contracts.h"

/* Parse a hex character functionality */
static inline bool parse_hex(int c, uint8_t *p) {
  REQUIRES(p != NULL);

  int v;
  if ('0' <= c && c <= '9') {
    v = c - '0';
  } else if ('A' <= c && c <= 'F') {
    v = c - 'A' + 10;
  } else if ('a' <= c && c <= 'f') {
    v = c - 'a' + 10;
  } else {
    return false;
  }

  ASSERT(0 <= v && v < 16);
  *p = v;
  return true;
}

/* Read a byte from a file
 * 
 * SUCCESSFUL BYTE PARSE: return true, *b = byte
 * END OF FILE: return false, *s = NULL
 * ERROR: return false *s = non-null string (client must free) */
static inline bool next_byte(FILE *F, uint8_t *b, char **s) {
  REQUIRES(F != NULL && b != NULL && s != NULL);

  // Scan for the first character
  int c;
  do {
    c = fgetc(F);

    // Advance over linecomments
    if (c == '#') {
      do { 
        c = fgetc(F);
      } while (c != '\n' && c != EOF);
    }

  } while (isspace(c));

  // Are we done?
  if (c == EOF) {
    *s = NULL; // No error
    return false;
  } 

  uint8_t hi;
  if (!parse_hex(c, &hi)) {
    *s = xcalloc(100, sizeof(char));
    sprintf(*s, "expected a hex character, found '%c'", c);
    return false;
  }

  // The next character must follow immediately
  int c2 = fgetc(F); 
  if (c2 == EOF) {
    *s = xcalloc(100, sizeof(char));
    sprintf(*s, "expected 2 hex chars, found '%c', then end of file", c);
    return false;
  }
  
  uint8_t lo;
  if (!parse_hex(c2, &lo)) {
    *s = xcalloc(100, sizeof(char));
    sprintf(*s, "expected 2 hex chars, found '%c%c'", c, c2);
    return false;
  }

  *b = hi << 4 | lo;
  return true;
}

/* Read in various integer types from the file, possibly aborting program */
uint32_t read_u32(FILE *F) {
  REQUIRES(F != NULL);
  uint8_t x[4];
  char* errmsg;
  if (!next_byte(F, x, &errmsg) || !next_byte(F, x+1, &errmsg) ||
      !next_byte(F, x+2, &errmsg) || !next_byte(F, x+3, &errmsg)) {
    if (errmsg == NULL) {
      fprintf(stderr, "Expected 4-byte sequence, found end of file.\n");
    } else {
      fprintf(stderr, "Error while reading 4-byte sequence: %s\n", errmsg);
      free(errmsg);
    }
    fclose(F);
    exit(1);
  }

  return ((uint32_t)x[0] << 24) |
    ((uint32_t)x[1] << 16) |
    ((uint32_t)x[2] << 8) |
    ((uint32_t)x[3]);
}

uint16_t read_u16(FILE *F) {
  REQUIRES(F != NULL);
  uint8_t x[2];
  char* errmsg;
  if (!next_byte(F, x, &errmsg) || !next_byte(F, x+1, &errmsg)) {
    if (errmsg == NULL) {
      fprintf(stderr, "Expected 2-byte sequence, found end of file.\n");
    } else {
      fprintf(stderr, "Error while reading 2-byte sequence: %s\n", errmsg);
      free(errmsg);
    }
    fclose(F);
    exit(1);
  }

  return ((uint16_t)x[0] << 8) | ((uint16_t)x[1]);
}

uint8_t read_u8(FILE *F) {
  REQUIRES(F != NULL);
  uint8_t x;
  char* errmsg;
  if (!next_byte(F, &x, &errmsg)) {
    if (errmsg == NULL) {
      fprintf(stderr, "Expected byte, found end of file.\n");
    } else {
      fprintf(stderr, "Error while reading byte: %s\n", errmsg);
      free(errmsg);
    }
    fclose(F);
    exit(1);
  }

  return x;
}

/* Read a bytecode file */
struct bc0_file* read_program(char *filename) {
  FILE *F = fopen(filename, "r");
  if (F == NULL) {
    fprintf(stderr, "Error: could not open file '%s'\n", filename);
    exit(1);
  }

  /* Check magic number */
  uint8_t x[4];
  char *errmsg;
  if (!next_byte(F, x, &errmsg) ||
      !next_byte(F, x+1, &errmsg) ||
      !next_byte(F, x+2, &errmsg) ||
      !next_byte(F, x+3, &errmsg)) {
    if (errmsg == NULL) {
      fprintf(stderr, "End of file reached while reading magic number.\n");
    } else {
      fprintf(stderr, "Error while trying to read magic number: %s\n", errmsg);
      free(errmsg);
    }
    fprintf(stderr, "Are you sure %s is a C0 bytecode file?.\n", filename);
    fclose(F);
    exit(1);
  } else if (x[0] != 0xC0 || x[1] != 0xC0 || x[2] != 0xFF || x[3] != 0xEE) {
    fprintf(stderr, "Magic number is %02X%02X%02X%02X, which is wrong\n",
            x[0], x[1], x[2], x[3]);
    fprintf(stderr, "Are you sure %s is a C0 bytecode file?.\n", filename);
    fclose(F);
    exit(1);
  }

  /* Populate struct */
  struct bc0_file* bc0 = xmalloc(sizeof(struct bc0_file));
  bc0->magic = 0xC0C0FFEE;
  size_t i = 4;   /* current bc0_file byte position */

  bc0->version = read_u16(F);
  i += 2;

  bc0->int_count = read_u16(F);
  i += 2;

  bc0->int_pool = xcalloc(bc0->int_count, sizeof(int32_t));
  for (size_t j = 0; j < bc0->int_count; j++) {
    bc0->int_pool[j] = read_u32(F);
    i += 4;
  }

  bc0->string_count = read_u16(F);
  i += 2;
  bc0->string_pool = xcalloc(bc0->string_count, sizeof(char));
  for (size_t j = 0; j < bc0->string_count; j++) {
    bc0->string_pool[j] = (char) read_u8(F);
    i++;
  }

  bc0->function_count = read_u16(F);
  i += 2;
  bc0->function_pool =
    xcalloc(bc0->function_count, sizeof(struct function_info));
  for (size_t j = 0; j < bc0->function_count; j++) {
    bc0->function_pool[j].num_args = read_u16(F);
    i += 2;
    bc0->function_pool[j].num_vars = read_u16(F);
    i += 2;
    bc0->function_pool[j].code_length = read_u16(F);
    i += 2;
    bc0->function_pool[j].code = 
      xcalloc(bc0->function_pool[j].code_length, sizeof(ubyte));
    for (size_t k = 0; k < bc0->function_pool[j].code_length; k++) {
      bc0->function_pool[j].code[k] = read_u8(F);
      i++;
    }
  }

  bc0->native_count = read_u16(F);
  i += 2;
  bc0->native_pool = xcalloc(bc0->native_count, sizeof(struct native_info));
  for (size_t j = 0; j < bc0->native_count; j++) {
    bc0->native_pool[j].num_args = read_u16(F);
    i += 2;
    bc0->native_pool[j].function_table_index = read_u16(F);
    i += 2;
  }

  fclose(F);
  return bc0;
}

void free_program(struct bc0_file *program)
{
  REQUIRES(program != NULL);

  free(program->int_pool);
  // Don't free the string pool, it's stack allocated
  // free(program->string_pool);

  for (size_t j = 0; j < program->function_count; j++)
    free(program->function_pool[j].code);
  free(program->function_pool);

  free(program->native_pool);
  free(program);
}
