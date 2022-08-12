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

struct Text {
    int nlines;
    int size;

    char *buffer;
    String *strings;
};


int file_size(FILE *stream);
int get_buffer_to_text(Text *text, FILE *stream);
int count_lines(Text *text);
int get_buffer_to_strings(Text *text);
int fill_strings_struct(Text *text);
int text_print_to_file(Text *text, FILE *output);

#endif