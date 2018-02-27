This code directory contains three examples:

1. (top level)
   Hash dictionaries with combined keys and value (entry type)
   Compile with
	# cc0 -d readfile.c0 hdict-client.c0 hdict.c0 hdict-main.c0

2. (key-value directory)
   Hash dictionaries with keys and values as separate entities
   Compile with
        # cd key-value
	# cc0 -d hdict-client.c0 hdict.c0 hdict-main.c0

3. (hset directory)
   Hash sets
   Compile with
        # cd hset
	# cc0 -d hash_string.c0 hset-client-produce.c0 hset.c0 hset-main.c0
