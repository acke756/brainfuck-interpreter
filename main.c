#include "bf.h"

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
