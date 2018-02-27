15-122 Principles of Imperative Computation
Lights Out

==========================================================

Files you won't modify:
   lib/contracts.h     - Contracts for C
   lib/xalloc.{c,h}    - NULL-checking allocation
   lib/boardutil.{c,h} - Useful Lights-Out relevant functions
   lib/hdict.{c,h}     - Dictionaries, implemented as hash tables
   lib/queue.{c,h}     - Queues
   lib/heap.{c,h}      - Priority queues, implementd as heaps
   lib/bitvector.c     - Interface to bit vectors
   Makefile            - Utility for building this project

Files you may extend:
   board-ht.h          - Interface to hashtables keyed by boards

Files that don't exist yet:
   bitvector.c         - Bit vector implementation
   bitvector-test.c    - Your unit tests for bit vectors (Optional)
   board-ht.c          - Bit vector hashtable wrapper implementation
   lightsout.c         - Lights out implementation (needs a main() function)

==========================================================

Compiling your bitvector unit tests
   % make bitvector-test
   % ./bitvector-test

Compiling and running your lights out solver (with -DDEBUG)
   % make
   % ./lightsout-d boards/board0.txt

Compiling and running your lights out solver (without -DDEBUG)
   % make
   % ./lightsout boards/board0.txt

==========================================================

Submitting with Andrew handin script:
   % handin lightsout lightsout.c board-ht.h board-ht.c bitvector.c

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf lightsoutsol.tgz lightsout.c board-ht.h board-ht.c bitvector.c
