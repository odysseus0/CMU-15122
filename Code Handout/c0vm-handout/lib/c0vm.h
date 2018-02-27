/* C0VM structs, function signatures, and opcodes
 * 15-122, Principles of Imperative Computation
 * William Lovas, Rob Simmons, and Tom Cortina
 */

#ifndef _C0VM_H_
#define _C0VM_H_

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include "c0vm_abort.h"

#define BYTECODE_VERSION 6

typedef int8_t byte;
typedef uint8_t ubyte;

/*** .bc0 file format, including function info and native info ***/

struct bc0_file {
  uint32_t magic;
  uint16_t version;
  
  /* integer and string constant pools */
  uint16_t int_count;
  int32_t *int_pool;
  
  /* string pool stores all strings consecutively with NUL terminators */
  uint16_t string_count;
  char *string_pool;
  
  /* bytecode and native function tables */
  uint16_t function_count;
  struct function_info *function_pool;
  uint16_t native_count;
  struct native_info *native_pool;
};

struct function_info {
  uint16_t num_args;
  uint16_t num_vars;
  uint16_t code_length;
  ubyte *code;
};

struct native_info {
  uint16_t num_args;
  uint16_t function_table_index;
};

/*** C0 Values ***/
/* type of arbitrary c0_values -- variables, operands, etc. */

enum c0_val_kind { C0_INTEGER, C0_POINTER };

typedef struct c0_value {
  enum c0_val_kind kind; 
  union {
    int32_t i;
    void *p;
  } payload;
} c0_value;

static inline c0_value int2val(int32_t i) {
  c0_value v;
  v.kind = C0_INTEGER;
  v.payload.i = i;
  return v;
}

static inline int32_t val2int(c0_value v) {
  if (v.kind != C0_INTEGER)
    c0_memory_error("Invalid cast from c0_value (a pointer) to an integer");
  return v.payload.i;
}

static inline c0_value ptr2val(void *p) {
  c0_value v;
  v.kind = C0_POINTER;
  v.payload.p = p;
  return v;
}

static inline void *val2ptr(c0_value v) {
  if (v.kind != C0_POINTER) 
    c0_memory_error("Invalid cast from c0_value (an integer) to a pointer");
  return v.payload.p;
}

static inline bool val_equal(c0_value v1, c0_value v2) {
  return v1.kind == v2.kind && (v1.kind == C0_INTEGER 
                                ? val2int(v1) == val2int(v2)
                                : val2ptr(v1) == val2ptr(v2));
}


/*** instruction opcodes ***/

enum instructions {
/* arithmetic operations */
  IADD = 0x60,
  IAND = 0x7E,
  IDIV = 0x6C,
  IMUL = 0x68,
  IOR = 0x80,
  IREM = 0x70,
  ISHL = 0x78,
  ISHR = 0x7A,
  ISUB = 0x64,
  IXOR = 0x82,

/* stack operations */
  DUP = 0x59,
  POP = 0x57,
  SWAP = 0x5F,

/* memory allocation */
  NEWARRAY = 0xBC,
  ARRAYLENGTH = 0xBE,
  NEW = 0xBB,

/* memory access */
  AADDF = 0x62,
  AADDS = 0x63,
  IMLOAD = 0x2E,
  AMLOAD = 0x2F,
  IMSTORE = 0x4E,
  AMSTORE = 0x4F,
  CMLOAD = 0x34,
  CMSTORE = 0x55,

/* local variables */
  VLOAD = 0x15,
  VSTORE = 0x36,

/* constants */
  ACONST_NULL = 0x01,
  BIPUSH = 0x10,
  ILDC = 0x13,
  ALDC = 0x14,

/* control flow */
  NOP = 0x00,
  IF_CMPEQ = 0x9F,
  IF_CMPNE = 0xA0,
  IF_ICMPLT = 0xA1,
  IF_ICMPGE = 0xA2,
  IF_ICMPGT = 0xA3,
  IF_ICMPLE = 0xA4,
  GOTO = 0xA7,
  ATHROW = 0xBF,
  ASSERT = 0xCF,

/* function calls and returns */
  INVOKESTATIC = 0xB8,
  INVOKENATIVE = 0xB7,
  RETURN = 0xB0
};

/*** The format of C0 arrays ***/

struct c0_array_header {
  int count;
  int elt_size;
  void *elems;
};
typedef struct c0_array_header c0_array;

/*** interface functions (used in c0vm-main.c) ***/

struct bc0_file *read_program(char *filename);
void free_program(struct bc0_file *program);

int execute(struct bc0_file *bc0);


#endif /* _C0VM_H_ */
