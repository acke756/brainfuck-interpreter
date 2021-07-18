#include <stdlib.h>
#include <stdbool.h>

#include "bf.h"

typedef struct test {
    bool (*fun)(void);
    char *name;
} test_t;

bool test_sanity(void) {
    return true;
}

int main(int argc, char **argv) {
    test_t testv[] = {
        {test_sanity, "Sanity check"},
    };
    size_t testc = sizeof(testv) / sizeof(test_t);

    for (test_t *test_p = testv; test_p != testv + testc; test_p++) {
        printf("%s: ", test_p->name);
        if (!((test_p->fun)())) {
            puts("FAILED");
        } else {
            puts("PASSED");
        }
    }

    return 0;
}
