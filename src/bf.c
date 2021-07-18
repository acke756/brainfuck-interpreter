#include "bf.h"

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
        return -1;
    }

    return 0;
}

int interpret(bf_context_t *context_p) {
    long start_pos = ftell(context_p->f);
    if (start_pos < 0) {
        return -1;
    }

    int in;

    for (int c = fgetc(context_p->f); c != EOF; c = fgetc(context_p->f)) {
        switch (c) {
            case '>':
                (context_p->ptr)++;
                if (context_p->ptr >= context_p->mem + context_p->mem_siz) {
                    return -1;
                }

                break;
            case '<':
                (context_p->ptr)--;
                if (context_p->ptr < context_p->mem) {
                    return -1;
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
                    return -1;
                }

                break;
            case ',':
                in = getchar();
                if (in == EOF) {
                    return -1;
                }

                *(context_p->ptr) = (char) in;
                break;
            case '[':
                if (*(context_p->ptr) != 0) {
                    int result = interpret(context_p);
                    if (result != 0) {
                        return result;
                    }

                    break;
                }

                int result = skip_to_matching_rb(context_p->f);
                if (result != 0) {
                    return result;
                }

                break;
            case ']':
                if (start_pos == 0) {
                    return -1;
                }

                if (*(context_p->ptr) == 0) {
                    return 0;
                }

                if (fseek(context_p->f, start_pos, SEEK_SET) < 0) {
                    return -1;
                }

                break;
        }
    }

    if (start_pos != 0) {
        return -1;
    }

    return 0;
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
        return -1;
    }

    int result = bf_interpret_file(f, mem_siz, mem);

    if (fclose(f) != 0) {
        return -1;
    }

    return result;
}
