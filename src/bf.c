#include "bf.h"

#define BF_SUCCESS 0
#define BF_ERR_UNMATCHED_LB 1
#define BF_ERR_UNMATCHED_RB 2
#define BF_ERR_OOB_LEFT 3
#define BF_ERR_OOB_RIGHT 4
#define BF_ERRCOUNT 5

#define BF_LIBERR_FTELL -1
#define BF_LIBERR_FSEEK -2
#define BF_LIBERR_PUTCHAR -3
#define BF_LIBERR_GETCHAR -4
#define BF_LIBERR_FOPEN -5
#define BF_LIBERR_FCLOSE -6
#define BF_LIBERRCOUNT -7

typedef struct bf_context {
    FILE *f;
    const size_t mem_siz;
    char *const mem;
    char *ptr;
} bf_context_t;

int skip_to_matching_rb(FILE *f) {
    int c;
    for (c = fgetc(f); c != EOF && c != ']'; c = fgetc(f)) {
        if (c == '[') {
            skip_to_matching_rb(f);
        }
    }

    if (c == EOF) {
        return BF_ERR_UNMATCHED_LB;
    }

    return BF_SUCCESS;
}

int interpret(bf_context_t *context_p) {
    long start_pos = ftell(context_p->f);
    if (start_pos < 0) {
        return BF_LIBERR_FTELL;
    }

    int in;

    for (int c = fgetc(context_p->f); c != EOF; c = fgetc(context_p->f)) {
        switch (c) {
            case '>':
                (context_p->ptr)++;
                if (context_p->ptr >= context_p->mem + context_p->mem_siz) {
                    return BF_ERR_OOB_RIGHT;
                }

                break;
            case '<':
                (context_p->ptr)--;
                if (context_p->ptr < context_p->mem) {
                    return BF_ERR_OOB_LEFT;
                }

                break;
            case '+':
                (*(context_p->ptr))++;
                break;
            case '-':
                (*(context_p->ptr))--;
                break;
            case '.':
                if (putchar(*(context_p->ptr)) == EOF) {
                    return BF_LIBERR_PUTCHAR;
                }

                break;
            case ',':
                in = getchar();
                if (in == EOF) {
                    return BF_LIBERR_GETCHAR;
                }

                *(context_p->ptr) = (char) in;
                break;
            case '[':
                if (*(context_p->ptr) != 0) {
                    int result = interpret(context_p);
                    if (result != BF_SUCCESS) {
                        return result;
                    }

                    break;
                }

                int result = skip_to_matching_rb(context_p->f);
                if (result != BF_SUCCESS) {
                    return result;
                }

                break;
            case ']':
                if (start_pos == 0) {
                    return BF_ERR_UNMATCHED_RB;
                }

                if (*(context_p->ptr) == 0) {
                    return BF_SUCCESS;
                }

                if (fseek(context_p->f, start_pos, SEEK_SET) < 0) {
                    return BF_LIBERR_FSEEK;
                }

                break;
        }
    }

    if (start_pos != 0) {
        return BF_ERR_UNMATCHED_LB;
    }

    return BF_SUCCESS;
}

int bf_interpret_file(FILE *f, const size_t mem_siz, char *const mem) {
    if (mem == NULL) {
        char new_mem[mem_siz];
        return bf_interpret_file(f, mem_siz, new_mem);
    }

    for (size_t i = 0; i < mem_siz; i++) {
        mem[i] = 0;
    }

    char *ptr = mem;

    bf_context_t context = {
        .f = f,
        .mem_siz = mem_siz,
        .mem = mem,
        .ptr = ptr,
    };

    return interpret(&context);
}

int bf_interpret(char *path, const size_t mem_siz, char *const mem) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return BF_LIBERR_FOPEN;
    }

    int result = bf_interpret_file(f, mem_siz, mem);

    if (fclose(f) != 0) {
        return BF_LIBERR_FCLOSE;
    }

    return result;
}

char const *bf_strerror(int err) {
    static char const *errs[BF_ERRCOUNT];
    errs[BF_SUCCESS] = "Success";
    errs[BF_ERR_UNMATCHED_LB] = "Unmatched '['";
    errs[BF_ERR_UNMATCHED_RB] = "Unmatched ']'";
    errs[BF_ERR_OOB_LEFT] = "Pointer out of bounds, too far left";
    errs[BF_ERR_OOB_RIGHT] = "Pointer out of bounds, too far right";

    static char const *liberrs[-1-BF_LIBERRCOUNT];
    liberrs[-1-BF_LIBERR_FTELL] = "ftell";
    liberrs[-1-BF_LIBERR_FSEEK] = "fseek";
    liberrs[-1-BF_LIBERR_PUTCHAR] = "putchar";
    liberrs[-1-BF_LIBERR_GETCHAR] = "getchar";
    liberrs[-1-BF_LIBERR_FOPEN] = "fopen";
    liberrs[-1-BF_LIBERR_FCLOSE] = "fclose";

    if (err < 0) {
        return liberrs[-1-err];
    }

    return errs[err];
}
