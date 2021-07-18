CC := gcc
CF = -g -Wall -Werror -Iinclude -o $@ $^

MC := valgrind --leak-check=full --show-leak-kinds=all

SRCS := $(shell find src -path "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
MAIN := ./main.c
TEST := ./test.c

EXE := ./bin/brainfuck
ARGS := bf/hello.bf

TESTEXE = ./bin/test

$(EXE): $(MAIN) $(OBJS)
	$(CC) $(CF)

$(TESTEXE): $(TEST) $(OBJS)
	$(CC) $(CF)

obj/%.o: src/%.c
	$(CC) -c $(CF)

.PHONY: run clean test memcheck memtest

test: $(TESTEXE)
	$<

run: $(EXE)
	$< $(ARGS)

clean:
	rm $(EXE) $(TESTEXE) $(OBJS)

memcheck: $(EXE)
	$(MC) $< $(ARGS)

memtest: $(TESTEXE)
	$(MC) $<
