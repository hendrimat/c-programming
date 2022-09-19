all: bfi

mem.o: mem.c
	gcc -c mem.c

bfi: mem.h mem.o
	gcc bfi.c mem.o -o bfi

clean:
	rm -fr mem.o bfi