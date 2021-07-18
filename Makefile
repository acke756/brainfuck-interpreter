CC := gcc
CF = -Wall -Werror -Iinclude -o $@ $^

SRCS := $(shell find src -path "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
MAIN := ./main.c
TEST := ./test.c

EXE := ./bin/brainfuck
TESTEXE = ./bin/test

$(EXE): $(MAIN) $(OBJS)
	$(CC) $(CF)

$(TESTEXE): $(TEST) $(OBJS)
	$(CC) $(CF)

obj/%.o: src/%.c
	$(CC) -c $(CF)

.PHONY: run clean test

test: $(TESTEXE)
	$(TESTEXE)

run: $(EXE)
	$< bf/test.bf

clean:
	rm $(EXE) $(TESTEXE) $(OBJS)
