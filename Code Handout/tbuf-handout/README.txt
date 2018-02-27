15-122 Principles of Imperative Computation
Text Buffers

==========================================================

Files you won't modify:
   tbuf-test.c0   - Test adapter for text buffers
   editor-test.c0 - Test adapter for editor
   test-main.c0   - Main test program
   lovas-E0.c0    - The E0 text editor implementation

Files you will modify:
   tbuf.c0        - Text buffer implemented as a doubly-linked lists of chars
   editor.c0      - Text buffers augmented with position tracking

==========================================================

Compiling and running the tbuf tests:
   % cc0 -d -w -o tbuf-test tbuf.c0 tbuf-test.c0 test-main.c0
   % ./tbuf-test
   

Compiling and running the 
   % cc0 -d -w -o editor-test tbuf.c0 editor.c0 editor-test.c0 test-main.c0
   % ./editor-test

Compiling and running the E0 editor:
   % cc0 -d -w -o E0 tbuf.c0 editor.c0 lovas-E0.c0
   % ./E0

==========================================================

Submitting with Andrew handin script:
   % handin tbuf tbuf.c0 editor.c0

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf tbufhandin.tgz tbuf.c0 editor.c0
