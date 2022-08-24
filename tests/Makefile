CFLAGS := -std=c99 -Wall -Wextra -Wconversion -Werror -pedantic -I../src

TARGETS := simple_asserts_test.out assert_with_message_test.out

all: $(TARGETS)

.PHONY: all

simple_asserts_test.out: simple_asserts_test.o
	$(CC) -o $@ $^

simple_asserts_test.o: simple_asserts_test.c

assert_with_message_test.out: assert_with_message_test.o
	$(CC) -o $@ $^

assert_with_message_test.o: assert_with_message_test.c

runtests:
	set -e; \
	for i in $(TARGETS); do \
		echo '==== Running' $$i; \
		./$$i; \
	done

clean:
	rm -f *.o $(TARGETS)
