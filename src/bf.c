#include "bf.h"

int bf_interpret_file(FILE *f, const size_t mem_siz, char *const mem) {
    if (mem == NULL) {
        char new_mem[mem_siz];
        return bf_interpret_file(f, mem_siz, new_mem);
    }

    char *ptr = mem;
    int in;

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
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '.':
                if (putchar(*ptr) == EOF) {
                    return -1;
                }

                break;
            case ',':
                in = getchar();
                if (in == EOF) {
                    return -1;
                }

                *ptr = (char) in;
                break;
        }
    }

    return 0;
}

int bf_interpret(char *path, const size_t mem_siz, char *const mem) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }

    int result = bf_interpret_file(f, mem_siz, mem);

    if (fclose(f) != 0) {
        return -1;
    }

    return result;
}
