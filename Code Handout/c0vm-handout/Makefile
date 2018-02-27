CC=gcc
# Note: if you're not working on Andrew AFS, change this to the root
# of your own C0 installation (this is /Users/rjsimmon/r/c0/cc0 on my
# system -rjs)
C0TOP=/afs/andrew/course/15/122
C0LIBDIR=$(C0TOP)/lib
C0RUNTIMEDIR=$(C0TOP)/runtime
CFLAGS=-Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -fwrapv
CFLAGSEXTRA=-L$(C0LIBDIR) -L$(C0RUNTIMEDIR) -Wl,-rpath $(C0LIBDIR) -Wl,-rpath $(C0RUNTIMEDIR) -limg -lstring -lcurses -largs -lparse -lfile -lconio -lbare -l15411

.PHONY: c0vm c0vmd clean
default: c0vm c0vmd

c0vm: c0vm.c c0vm_main.c
	$(CC) $(CFLAGS) -o c0vm c0vm_main.c c0vm.c lib/c0vm_c0ffi.c lib/c0vm_abort.c lib/read_program.c lib/stack.c lib/c0v_stack.c lib/xalloc.c $(CFLAGSEXTRA)

c0vmd: c0vm.c c0vm_main.c
	$(CC) $(CFLAGS) -DDEBUG -o c0vmd c0vm_main.c c0vm.c lib/c0vm_c0ffi.c lib/c0vm_abort.c lib/read_program.c lib/stack.c lib/c0v_stack.c lib/xalloc.c $(CFLAGSEXTRA)

clean:
	rm -Rf c0vm c0vmd
