This code directory contains the following progression:

1. Hash dictionaries updated with void* for entry and key
   a. Word count example
	# cc0 -d hdict-void.c1 readfile.c0 words-void.c1 words-main-void.c1
   b. Produce example
        # cc0 -d hdict-void.c1 produce-void.c1 produce-main-void.c1

   c. Doesn't work in combination
   	# cc0 -d hdict-void.c1 readfile.c0 words-void.c1 produce-void.c1 words-main-void.c1


2. Generic hash dictionaries (with void* and function pointers)
	# cc0 -d hdict.c1 readfile.c0 words.c1 produce.c1 main.c1
