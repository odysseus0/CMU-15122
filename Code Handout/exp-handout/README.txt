15-122 Principles of Imperative Computation
Clac and EXP

==========================================================

Files you won't modify:
   lib/stack_of_int.c0             - Stacks containing integers (istack_t)
   lib/stack_of_string.c0          - Stacks containing strings (sstack_t)
   lib/queue_of_string.c0          - Queues containing strings (queue_t)
   lib/stack_of_stack_of_string.c0 - Stacks containing stacks of strings
   lib/utils.c0                    - Library for populating queues of strings
   clac-main.c0                    - Runs clac read-eval-print loop (REPL)
   exp-main.c0                     - Runs EXP read-eval-print loop (REPL)

Files that don't exist yet
   clac.c0               - Clac interpreter
   parse.c0              - Parser for turning EXP programs into Clac

Files you will modify:
   dict.c0               - Precedence dictionary implementation
   exp-defs.clac         - Clac definitions for missing EXP operations

   clac-test.c0          - Testing the Clac implementation (Optional)
   dict-test.c0          - Testing the dict implementation (Optional)
   exp-test.c0           - Testing the EXP implementation (Optional)

==========================================================

Running the reference implementation of the Claculator (Andrew Linux only):
   Run without tracing, but with the exp-defs.clac definitions loaded
   % clac-ref exp-defs.clac
   clac>> 8 5 ==
   clac>> 4 3 * 7 5 + == 1 && 1 ==

   Run with tracing, without the exp-defs.clac definitions loaded
   % clac-ref -trace
   clac>> 8 5 4 - + dup
   clac>> print print
   clac>> quit

Compiling and running the Claculator:
   % cc0 -d -w -o clac lib/*.c0 clac.c0 clac-main.c0
   % ./clac

Compiling and running Clac test cases:
   % cc0 -d -w -o clac-test lib/*.c0 clac.c0 clac-test.c0
   % ./clac-test

Compiling and running the dictionary and provided tests:
   % cc0 -d -w -o dict-test lib/*.c0 dict.c0 dict-test.c0
   % ./dict-test

Compiling and running the parser:
   % cc0 -d -w -o exp lib/*.c0 clac.c0 dict.c0 parse.c0 exp-main.c0
   % ./exp
   EXP>> 1 + 3 * 4 == 13
   % ./exp -x
   EXP>> 1 + -3 * 4 / -2 ** 3

Compiling and running the parser tests:
   % cc0 -d -w -o exp-test lib/*.c0 clac.c0 dict.c0 parse.c0 exp-test.c0
   % ./exp-test

==========================================================

Submitting with Andrew handin script:
   % handin exp clac.c0 dict.c0 parse.c0 exp-defs.clac

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf exphandin.tgz clac.c0 dict.c0 parse.c0 exp-defs.clac
