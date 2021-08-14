#include "bf.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    int result = bf_interpret(argv[1], 30000, NULL);
    if (result > 0) {
        printf("Error: %s\n", bf_strerror(result));
        return -1;
    } else if (result < 0) {
        perror(bf_strerror(result));
        return -1;
    }

    return 0;
}
