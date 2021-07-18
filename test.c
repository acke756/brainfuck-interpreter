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

bool test_leave_left(void) {
    return bf_interpret("bf/leave_left.bf", 4, NULL) != 0;
}

bool test_leave_right(void) {
    return bf_interpret("bf/four_right.bf", 4, NULL) != 0;
}

int main(int argc, char **argv) {
    test_t testv[] = {
        {test_sanity, "Sanity check"},
        {test_leave_left, "Error when pointer exits left"},
        {test_leave_right, "Error when pointer exits right"},
    };
    size_t testc = sizeof(testv) / sizeof(test_t);

    for (test_t *test_p = testv; test_p != testv + testc; test_p++) {
        if (!((test_p->fun)())) {
            printf("FAILED");
        } else {
            printf("PASSED");
        }

        printf(": %s\n", test_p->name);
    }

    return 0;
}
