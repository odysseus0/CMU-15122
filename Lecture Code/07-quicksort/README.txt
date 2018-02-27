To test mergesort/quicksort, uncomment the appropriate line in the
sort function in file sort-test.c0 and sort-time.c0

Compile with

cc0 -d arrayutil.c0 sortlib.c0 sort.c0 sort-test.c0

./a.out

which will test sorting a random array of about 500 elements and
repeat this 10 times.  This will be slow since contracts are checked
dynamically, testing your code.

cc0 arrayutil.c0 sortlib.c0 sort.c0  sort-time.c0
time ./a.out -r number of runs> -exp <log_2 of number_of_element>

times sorting a random array of size <size>, repeating <repeat> times.
Doubling the input size should roughly four-fold increase the running
time, since selecting sort has quadratic asymptotic complexity.

E.g.
# time ./a.out -r 200 -exp 10
# time ./a.out -r 200 -exp 11
# time ./a.out -r 200 -exp 12
