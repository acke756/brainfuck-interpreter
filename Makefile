CC := gcc
CF = -Wall -Werror -o $@ $^

EXE := ./bin/brainfuck
MAIN := ./main.c

$(EXE): $(MAIN)
	$(CC) $(CF)

.PHONY: run clean

run: $(EXE)
	$< bf/test.bf

clean:
	rm $(EXE)
