15-122 Principles of Imperative Computation
Ropes

==========================================================

Files you won't modify:
   hdict.c1          - Generic dictionaries using hashtables
                       (respect the interface!)

Files you will modify:
   rope.c1           - Interface of ropes 
                       (you may optionally add new functions)

Files that don't exist yet:
   rope-test.c0      - Test file with a main() function 
                       (optional, highly recommended!)

==========================================================

Compiling and running your code:
   % cc0 -d -o rope-test hdict.c1 rope.c1 rope-test.c0
   % ./rope-test

==========================================================

Submitting with Andrew handin script:
   % handin ropes rope.c1 rope-test.c0
or
   % handin ropes rope.c1

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf ropehandin.tgz rope.c1 rope-test.c0
or
   % tar -czvf ropehandin.tgz rope.c1
