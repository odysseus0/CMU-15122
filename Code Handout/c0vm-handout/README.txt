15-122 Principles of Imperative Computation
The C0VM

==========================================================

Useful information:
   C_IDOMS.txt            - Describes some of the goofy C stuff in the VM
   PROG_HINTS.txt         - Some hints on the tricky RETURN case
   c0vm-ref.txt           - Bytecode implementation reference

Files you won't modify:
   lib/contracts.h        - Contracts for C
   lib/xalloc.{c,h}       - NULL-checking allocation
   lib/stack.{c,h}        - Stacks (with O(1) stack_size!)
   lib/c0v_stack.{c,h}    - C0 Value Stacks (with O(1) stack_size!)
   lib/c0vm_abort.{c,h}   - Functions for your C0VM to report runtime errors
   lib/c0vm_c0ffi.{c,h}   - Interface to the library functions
   lib/c0vm.h             - Header file, contains C0VM types and functions
   lib/read_program.{c,h} - Reading in C0 bytecode from a file
   c0vm_main.c            - Main function - loads bytecode, handles return

Files you will modify:
   c0vm.c                 - Executes C0 bytecode

==========================================================

Compiling a C0 program to create a .bc0 file (produces tests/iadd.bc0):
   % cc0 -b tests/iadd.c0

Compiling and running your C0VM implementaiton (with -DDEBUG)
(Must compile iadd.c0 to iadd.bc0 first)
   % make
   % ./c0vmd tests/iadd.bc0

Compiling and running your C0VM implementation (without -DDEBUG)
(Must compile iadd.c0 to iadd.bc0 first)
   % make
   % ./c0vm tests/iadd.bc0

==========================================================

Submitting with Andrew handin script (CHECKPOINT):
   % handin c0vm-check c0vm.c

Submitting with Andrew handin script (FINAL):
   % handin c0vm-final c0vm.c

Creating a tarball to submit with autolab.autolab.cmu.edu web interface:
   % tar -czvf c0vmsol.tgz c0vm.c


