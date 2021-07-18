#include "bf.h"

int bf_interpret_file(FILE *f, const size_t mem_siz) {
    char mem[mem_siz];
    char *ptr = mem;

    for (size_t i = 0; i < mem_siz; i++) {
        mem[i] = 0;
    }

    for (int c = fgetc(f); c != EOF; c = fgetc(f)) {
        switch (c) {
            case '>':
                ptr++;
                if (ptr >= mem + mem_siz) {
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

int bf_interpret(char *path, const size_t mem_siz) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }

    int result = bf_interpret_file(f, mem_siz);

    if (fclose(f) != 0) {
        return -1;
    }

    return result;
}
