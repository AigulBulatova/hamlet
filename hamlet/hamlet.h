#pragma once

#include <stdio.h>      
#include <stdlib.h>
#include <string.h>

struct String { 
    int number;
    size_t len;

    char *string_ptr;
};

struct Text {
    int nlines;
    size_t size;

    char *buffer;
    String *strings;
};


int file_size(Text *text, FILE *stream);
int get_buffer_to_text(Text *text, FILE *stream);
int count_lines(Text *text);
int string_alloc(Text *text);
int fill_strings_struct(Text *text);
void struct_init(Text *text);
int text_print_to_file(Text *text, FILE *output);
int text_processing(FILE *stream);
