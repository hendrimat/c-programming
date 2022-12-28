CFLAGS := -std=c17 -g -Werror -Wall -Wpedantic
INC := inc # Päisefailid

EXE := lib/interpreter

# Lähtekood (kõik src/.c failid)
SRCS := $(wildcard src/*.c)

# Objektfailid
LIBS := $(patsubst src/%.c, obj/%.o, $(SRCS))

# tulemus : nõuded (prerequisites)
lib/interpreter: $(LIBS)
	gcc -I$(INC) $(CFLAGS) $(LIBS) -o $(EXE)

# $@ - kompileerimise tulemus ehk %.o (nt stack.o)
# $< - kompileerimise alus    ehk %.c (nt stack.c)
obj/%.o: src/%.c
	gcc -I$(INC) -c $(CFLAGS) -o $@ $<

obj:
	mkdir -p obj

lib:
	mkdir -p lib

# See on lihtsalt käsk
.PHONY: run
run: $(EXE)
	./$(EXE)

.PHONY: clean
clean:
	rm -rf obj/* lib/*