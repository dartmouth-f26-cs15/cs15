.PHONY: all clean fmt

CC ?= clang
CFLAGS ?= -Wall -Wextra -Wpedantic -Wvla -Wshadow -fPIC -std=c23 -g

all: malloc.so

malloc.o: malloc.c
	$(CC) $(CFLAGS) $^ -c -o $@

cs15_malloc.o: cs15_malloc.c
	$(CC) $(CFLAGS) $^ -c -o $@

malloc.so: malloc.o cs15_malloc.o
	$(CC) $(CFLAGS) $^ -shared -o $@

fmt:
	clang-format --style='{IndentWidth: 4, AllowShortFunctionsOnASingleLine: false}' -i *.c *.h

clean:
	rm -f *.so *.o
