CFLAGS := -std=c99 -g -Werror -Wall -Wpedantic
INC := inc # Päisefailid

# Lähtekood (kõik src/.c failid)
SRCS := $(wildcard src/*.c)

# Objektfailid
LIBS := $(patsubst src/%.c, obj/%.o, $(SRCS))

# tulemus : nõuded (prerequisites)
lib/interpreter: $(LIBS) lib
	gcc -I$(INC) $(CFLAGS) $(LIBS) -o lib/interpreter

# $@ - kompileerimise tulemus ehk %.o (nt stack.o)
# $< - kompileerimise alus    ehk %.c (nt stack.c)
obj/%.o: src/%.c obj
	gcc -I$(INC) -c $(CFLAGS) -o $@ $<

obj:
	mkdir -p obj

lib:
	mkdir -p lib

# See on lihtsalt käsk
.PHONY: run
run: lib/interpreter
	./lib/interpreter

.PHONY: clean
clean:
	rm -rf obj/ lib/