CC=gcc -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g 
CCD=gcc -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -DDEBUG

# Compiles the student solution
graphtest: *.c *.h lib/*.c lib/*.h
	$(CCD) lib/*.c graph.c graph-search.c graph-test.c -o $@

# Compiles the instructor solution
graphtest-sol: *.c *.h lib/*.c lib/*.h
	$(CCD) lib/*.c graph-sol.c graph-search.c graph-test.c -o $@
