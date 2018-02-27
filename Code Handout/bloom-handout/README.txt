15-122 Principles of Imperative Computation
Bloom Filters

==========================================================

Files you won't modify:
   bloom-worst.c0     - Sets that always return "true" for membership tests
   bloom-expensive.c0 - Memory and time expensive "perfect" sets

Files that don't exist yet
   bloom-test.c0      - Unit tests, performance test (Task 1)
   bloom1.c0          - Bloom filters as arrays of bool, single hash (Task 2)
   bloom2.c0          - Bloom filters as arrays of int, 3 hashes (Tasks 3-5)

==========================================================

Running your test cases against the various implementations:
   % cc0 -d -w -x bloom-worst.c0 bloom-test.c0
   % cc0 -d -w -x bloom-expensive.c0 bloom-test.c0
   % cc0 -d -w -x bloom1.c0 bloom-test.c0
   % cc0 -d -w -x bloom2.c0 bloom-test.c0

==========================================================

Submitting to the unofficial test case checker with the Andrew handin script:
   % handin bloomcheck bloom-test.c0

Submitting offically:
   % handin bloom bloom-test.c0 bloom1.c0 bloom2.c0

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf bloomhandin.tgz bloom-test.c0 bloom1.c0 bloom2.c0
