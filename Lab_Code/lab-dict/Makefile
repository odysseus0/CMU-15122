test-gen-dict:
	@cc0 -x gen-dict.c1 test-gen-dict-1.c1
	@cc0 -x gen-dict.c1 test-gen-dict-2.c1
	@echo 'Tests passed! Move on to (4.a)'

time-lcs-slow:
	@cc0 lcs-slow.c1 lcs-test.c1
	time ./a.out
	rm -f ./a.out

time-lcs-fast:
	@cc0 gen-dict.c1 lcs-fast.c1 lcs-test.c1
	time ./a.out
	rm -f ./a.out
