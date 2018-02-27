Compile with
# cc0 arrayutil.c0 search.c0 search-time.c0
Note: arrayutil.c0 is only needed for compiling the sorted version of search.

Execute as
# time ./a.out -r <number of runs> -n <number of elements>
E.g.
# time ./a.out -r 200 -n 1000000
# time ./a.out -r 200 -n 2000000
# time ./a.out -r 200 -n 4000000
