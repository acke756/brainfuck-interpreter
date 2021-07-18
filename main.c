#include "bf.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    if (bf_interpret(argv[1], 30000) != 0) {
        perror("Error: ");
        return -1;
    }

    return 0;
}
