CCBIN=gcc
#CCBIN=/usr/bin/gcc
CC=$(CCBIN) -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g
CCD=$(CCBIN) -Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -DDEBUG
C_LIBS=lib/xalloc.c lib/hdict.c lib/queue.c lib/boardutil.c lib/heap.c

default: lightsout lightsout-d

lightsout: $(C_LIBS) lib/*.h bitvector.c board-ht.c lightsout.c
	$(CC) -O3 -o lightsout $(C_LIBS) bitvector.c board-ht.c lightsout.c

lightsout-d: $(C_LIBS) lib/*.h bitvector.c board-ht.c lightsout.c
	$(CCD) -o lightsout-d $(C_LIBS) bitvector.c board-ht.c lightsout.c

bitvector-test: $(C_LIBS) lib/*.h bitvector.c bitvector-test.c
	$(CCD) -o bitvector-test $(C_LIBS) bitvector.c bitvector-test.c

.PHONY: clean
clean:
	rm -Rf *.o lib/*.o lightsout lightsout-d bitvector-test *.dSYM
