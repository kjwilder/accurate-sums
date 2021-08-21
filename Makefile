CC=g++
CCOPTS=-Wall -g

tests: test1 test2 test3

test1 : test1.cc
	$(CC) test1.cc $(CCOPTS) -o $@

test2 : test2.cc
	$(CC) test2.cc $(CCOPTS) -o $@

test3 : test3.cc
	$(CC) test3.cc $(CCOPTS) -o $@

clean ::
	/bin/rm -rf test? *.dSYM

