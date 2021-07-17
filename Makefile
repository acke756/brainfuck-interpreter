CC := gcc
CF = -Wall -Werror -Iinclude -o $@ $^

SRCS := $(shell find src -path "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
MAIN := ./main.c
EXE := ./bin/brainfuck

$(EXE): $(MAIN) $(OBJS)
	$(CC) $(CF)

obj/%.o: src/%.c
	$(CC) -c $(CF)

.PHONY: run clean

run: $(EXE)
	$< bf/test.bf

clean:
	rm $(EXE) $(OBJS)
