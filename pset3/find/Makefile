#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

all: find generate sort_test

find: find.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o find find.c helpers.c -lcs50 -lm

generate: generate.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o generate generate.c

sort_test: sort_test.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o sort_test sort_test.c helpers.c -lcs50 -lm

clean:
	rm -f *.o a.out core find generate
