CC = gcc
CFLAGS = -Wall -g
TARGETS = calculator child

all: $(TARGETS)

calculator: calculator.c
	$(CC) $(CFLAGS) -o calculator calculator.c

child: child.c
	$(CC) $(CFLAGS) -o child child.c

clean:
	rm -f $(TARGETS) *.o

# Test targets - compile and run each testcase
test1: all
	./calculator testcase_dir/testcase1

test2: all
	./calculator testcase_dir/testcase2

test3: all
	./calculator testcase_dir/testcase3

test4: all
	./calculator testcase_dir/testcase4

test5: all
	./calculator testcase_dir/testcase5
