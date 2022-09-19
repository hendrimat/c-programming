all: main

stack.o: stack.c
	gcc -c stack.c

main: stack.h stack.o
	gcc main.c stack.o -o main

clean:
	rm -fr stack.o main