Transforms the program in simple.c0 and test.c0 into C.

To compile the resulting C program (on a Unix/Linux/Mac environment), execute
- Either
  # gcc -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -DDEBUG lib/*.c test.c simple.c
- or
  # make


To compile the program in tree.c, execute
- Either
  # gcc -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -DDEBUG lib/*.c tree.c
- or
  # make tree
