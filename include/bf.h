#pragma once

#include <stdio.h>

int bf_interpret_file(FILE *f, const size_t mem_siz, char *const mem);

int bf_interpret(char *path, const size_t mem_siz, char *const mem);

char const *bf_strerror(int err);
