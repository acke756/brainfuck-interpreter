#include "bf.h"

#define MEM_SIZ 30000

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
