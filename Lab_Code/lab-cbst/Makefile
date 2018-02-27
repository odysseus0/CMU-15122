.PHONY: default bst-test bst-test-d

default: bst-test-d bst-test

bst-test-d:
	gcc -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -DDEBUG -o bst-test-d lib/*.c bst.c bst-test.c

bst-test:
	gcc -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -o bst-test lib/*.c bst.c bst-test.c
