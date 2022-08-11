#include <stdio.h>
#include "hamlet.h"

int main()
{
    FILE *lineptr = fopen("hamlet.txt", "r");
    printf("%d", count_lines(lineptr));
}