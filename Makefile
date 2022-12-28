CFLAGS := -std=c17 -g -Werror -Wall -Wpedantic -m32
INC := inc # Päisefailid

EXE := lib/compiler

# Lähtekood (kõik src/.c failid)
SRCS := $(wildcard src/*.c)

# Objektfailid
LIBS := $(patsubst src/%.c, obj/%.o, $(SRCS))

.PHONY: compiler
compiler: $(LIBS)
	gcc -I$(INC) $(CFLAGS) $(LIBS) -o $(EXE)

# $@ - kompileerimise tulemus ehk %.o (nt stack.o)
# $< - kompileerimise alus    ehk %.c (nt stack.c)
obj/%.o: src/%.c
	gcc -I$(INC) -c $(CFLAGS) -o $@ $<

obj:
	mkdir -p obj

lib:
	mkdir -p lib


.PHONY: run
run: $(EXE)
	./$(EXE) '>++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.' > hello.asm
	nasm -felf hello.asm -o ./obj/hello.o
	gcc -m32 -no-pie ./obj/mem.o ./obj/hello.o -o hello
	./hello

.PHONY: clean
clean:
	rm -rf obj/* lib/* hello*