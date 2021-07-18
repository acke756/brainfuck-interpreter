#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "bf.h"

#define RED "\033[31m"
#define GRN "\033[32m"
#define RST "\033[0m"

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

bool test_four_rising(void) {
    char mem_ref[] = {0, 1, 2, 3};
    char mem[4] = {0};

    bf_interpret("bf/four_rising.bf", 4, mem);

    return memcmp(mem, mem_ref, 4UL) == 0;
}

bool test_four_falling(void) {
    char mem_ref[] = {0, -1, -2, -3};
    char mem[4] = {0};

    bf_interpret("bf/four_falling.bf", 4, mem);

    return memcmp(mem, mem_ref, 4UL) == 0;
}

bool test_conditional_skip(void) {
    char mem_ref[4] = {0};
    char mem[4] = {0};

    bf_interpret("bf/skip.bf", 4, mem);

    return memcmp(mem, mem_ref, 4UL) == 0;
}

bool test_loop(void) {
    char mem_ref[] = {3, 2, 1, 0};
    char mem[4] = {0};

    bf_interpret("bf/loop.bf", 4, mem);

    return memcmp(mem, mem_ref, 4UL) == 0;
}

bool test_left_bracket(void) {
    return bf_interpret("bf/left_bracket.bf", 4, NULL) != 0;
}

bool test_right_bracket(void) {
    return bf_interpret("bf/right_bracket.bf", 4, NULL) != 0;
}

int main(int argc, char **argv) {
    test_t testv[] = {
        {test_sanity, "Sanity check"},
        {test_leave_left, "Error when pointer exits left"},
        {test_leave_right, "Error when pointer exits right"},
        {test_four_rising, "Four rising numbers"},
        {test_four_falling, "Four falling numbers"},
        {test_conditional_skip, "Conditional skip"},
        {test_loop, "Loop"},
        {test_left_bracket, "Unmatched left bracket"},
        {test_right_bracket, "Unmatched right bracket"},
    };
    size_t testc = sizeof(testv) / sizeof(test_t);

    unsigned int fails = 0;
    for (test_t *test_p = testv; test_p != testv + testc; test_p++) {
        if (!((test_p->fun)())) {
            printf(RED "FAILED" RST);
            fails++;
        } else {
            printf(GRN "PASSED" RST);
        }

        printf(": %s\n", test_p->name);
    }

    puts("");

    if (fails == 0) {
        puts(GRN "All tests passed" RST);
    } else {
        printf(RED "%d test(s) failed!\n" RST, fails);
    }

    return 0;
}
