#
# Makefile
#
# Computer Science 50
# Section 7
#

all: linkedlist hash

hash: hash.c
	clang -ggdb3 -Ispl/include -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o hash hash.c -Lspl/lib -lm

linkedlist: linkedlist.c Makefile
	clang -ggdb3 -Ispl/include -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o linkedlist linkedlist.c -Lspl/lib -lm

clean:
	rm -f *.o core hash linkedlist
