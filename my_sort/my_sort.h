#pragma once

//------------------------------------------------------------------

#include <stdio.h>
#include "../hamlet/hamlet.h"

//------------------------------------------------------------------

int direct_compare      (const void *str1, const void *str2);

int reverse_compare     (const void *str1, const void *str2);

long my_partition       (char* base, long left, long right, long size, int (*cmp) (const void*, const void*));

int text_sort_and_print (Text *text, FILE *direct, FILE *reverse);

void my_qsort (void *base_el, long n, long size, int (*cmp) (const void* , const void* ));

void swap     (char* first, char* second, size_t size);