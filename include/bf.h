#pragma once

#include <stdio.h>

int bf_interpret_file(FILE *f, const size_t mem_siz);

int bf_interpret(char *path, const size_t mem_siz);
