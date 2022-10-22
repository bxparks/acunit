CFLAGS := -std=c99 -Wall -Wextra -Wconversion -Werror -pedantic -I../src

TARGETS := simple_asserts_test.out advanced_asserts_test.out

all: $(TARGETS)

.PHONY: all

simple_asserts_test.out: simple_asserts_test.o
	$(CC) -o $@ $^

simple_asserts_test.o: simple_asserts_test.c

advanced_asserts_test.out: advanced_asserts_test.o
	$(CC) -o $@ $^

advanced_asserts_test.o: advanced_asserts_test.c

runtests:
	set -e; \
	for i in $(TARGETS); do \
		echo '==== Running' $$i; \
		./$$i; \
	done

clean:
	rm -f *.o $(TARGETS)
