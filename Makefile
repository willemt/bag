GCOV_OUTPUT = *.gcda *.gcno *.gcov 
GCOV_CCFLAGS = -fprofile-arcs -ftest-coverage
CC     = gcc
CCFLAGS = -g -O2 -Wall -Werror -W -fno-omit-frame-pointer -fno-common -fsigned-char $(GCOV_CCFLAGS)


all: tests

main.c:
	sh make-tests.sh > main.c

tests: main.c bag.o test_bag.c CuTest.c main.c
	$(CC) $(CCFLAGS) -o $@ $^
	./tests
	gcov main.c test_bag.c bag.c

bag.o: bag.c
	$(CC) $(CCFLAGS) -c -o $@ $^

clean:
	rm -f main.c bag.o tests $(GCOV_OUTPUT)
