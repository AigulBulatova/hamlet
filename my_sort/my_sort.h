#pragma once

//------------------------------------------------------------------

#include <stdio.h>

//------------------------------------------------------------------

//int my_sort     (void *base, size_t num, size_t size, int (*compare) (const void *str1, const void *str2));

int straight_compare (const void *str1, const void *str2);

int reverse_compare  (const void *str1, const void *str2);
