#include <stdio.h>

#define MEM_SIZ 30000

////////////////////////////////////////////////////////////////////////////////
// Abstraction level -1
////////////////////////////////////////////////////////////////////////////////

int bf_interpret(FILE *f) {
    char mem[MEM_SIZ] = {0};
    char *ptr = mem;

    for (int c; c != EOF; c = fgetc(f)) {
        switch (c) {
            case '>':
                ptr++;
                if (ptr >= mem + MEM_SIZ) {
                    return -1;
                }

                break;
            case '<':
                ptr--;
                if (ptr < mem) {
                    return -1;
                }

                break;
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Abstraction level 0
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("fopen");
        return -1;
    }

    bf_interpret(f);

    if (fclose(f) != 0) {
        perror("fclose");
        return -1;
    }

    return 0;
}
