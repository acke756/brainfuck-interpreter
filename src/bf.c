#include "bf.h"

#define MEM_SIZ 30000

int bf_interpret_file(FILE *f) {
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

int bf_interpret(char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }

    int result = bf_interpret_file(f);

    if (fclose(f) != 0) {
        return -1;
    }

    return result;
}
