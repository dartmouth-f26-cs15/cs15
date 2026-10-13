.PHONY: all clean
all: mystery

mystery: mystery.s
	gcc -nostdlib -static $^ -o $@

clean:
	rm -rf mystery
