#ifndef HAMLET_H
#define HAMLET_H

#include <stdio.h>      
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct String {
    int number;
    int len;

    char *string_ptr;
};
struct Hamlet {
    int nlines;
    int size;

    char *buffer;
    String *strings;
};


int file_size(FILE *stream);

#endif