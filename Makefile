CC=g++
CCOPTS=-Wall -g -std=c++11

all :: test1 test2 test3

test1 : test1.cc sum.h
	$(CC) test1.cc $(CCOPTS) -o $@

test2 : test2.cc sum.h
	$(CC) test2.cc $(CCOPTS) -o $@

test3 : test3.cc sum.h
	$(CC) test3.cc $(CCOPTS) -o $@

clean ::
	/bin/rm -rf test? *.dSYM

