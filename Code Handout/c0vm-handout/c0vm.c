#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "lib/xalloc.h"
#include "lib/stack.h"
#include "lib/contracts.h"
#include "lib/c0v_stack.h"
#include "lib/c0vm.h"
#include "lib/c0vm_c0ffi.h"
#include "lib/c0vm_abort.h"

/* call stack frames */
typedef struct frame_info frame;
struct frame_info {
  c0v_stack_t S; /* Operand stack of C0 values */
  ubyte *P;      /* Function body */
  size_t pc;     /* Program counter */
  c0_value *V;   /* The local variables */
};

int execute(struct bc0_file *bc0) {
  REQUIRES(bc0 != NULL);

  /* Variables */
  c0v_stack_t S; /* Operand stack of C0 values */
  ubyte *P;      /* The array of bytes that make up the current function */
  size_t pc;     /* Your current location within the current byte array P */
  c0_value *V;   /* The local variables (you won't need this till Task 2) */
  (void) V;

  /* The call stack, a generic stack that should contain pointers to frames */
  /* You won't need this until you implement functions. */
  gstack_t callStack; 
  (void) callStack;

  while (true) {
    
#ifdef DEBUG
    /* You can add extra debugging information here */
    fprintf(stderr, "Opcode %x -- Stack size: %zu -- PC: %zu\n",
            P[pc], c0v_stack_size(S), pc);
#endif
    
    switch (P[pc]) {
      
    /* Additional stack operation: */

    case POP: {
      pc++;
      c0v_pop(S);
      break;
    }

    case DUP: {
      pc++;
      c0_value v = c0v_pop(S);
      c0v_push(S,v);
      c0v_push(S,v);
      break;
    }
      
    case SWAP: 


    /* Returning from a function.
     * This currently has a memory leak! It will need to be revised
     * when you write INVOKESTATIC. */

    case RETURN: {
      int retval = val2int(c0v_pop(S));
      assert(c0v_stack_empty(S));
#ifdef DEBUG
      fprintf(stderr, "Returning %d from execute()\n", retval);
#endif
      // Free everything before returning from the execute function!
      return retval;
    }


    /* Arithmetic and Logical operations */

    case IADD:
      
    case ISUB:
      
    case IMUL:
      
    case IDIV:
      
    case IREM:
      
    case IAND:
      
    case IOR:
      
    case IXOR:
      
    case ISHL:
      
    case ISHR:
      
      
    /* Pushing constants */

    case BIPUSH:

    case ILDC:
      
    case ALDC:

    case ACONST_NULL:


    /* Operations on local variables */

    case VLOAD:
      
    case VSTORE:
      
      
    /* Control flow operations */

    case NOP:
      
    case IF_CMPEQ:
      
    case IF_CMPNE:
      
    case IF_ICMPLT:
      
    case IF_ICMPGE:
      
    case IF_ICMPGT:
      
    case IF_ICMPLE:
      
    case GOTO:
      
    case ATHROW:

    case ASSERT:


    /* Function call operations: */

    case INVOKESTATIC:
      
    case INVOKENATIVE:


    /* Memory allocation operations: */

    case NEW:
      
    case NEWARRAY:
      
    case ARRAYLENGTH:


    /* Memory access operations: */

    case AADDF:
      
    case AADDS:
      
    case IMLOAD:
      
    case IMSTORE:
      
    case AMLOAD:
      
    case AMSTORE:
      
    case CMLOAD:
      
    case CMSTORE:
      
    default:
      fprintf(stderr, "invalid opcode: 0x%02x\n", P[pc]);
      abort();
    }
  }
  
  /* cannot get here from infinite loop */
  assert(false);
}

