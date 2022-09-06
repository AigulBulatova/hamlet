#pragma once
#include <stdio.h>

int sort (void *base, size_t num, size_t size, int (*compare) (const char*, const char*));
int compare (const void *arg1, const void *arg2);
