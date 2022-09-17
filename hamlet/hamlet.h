#pragma once

//------------------------------------------------------------------

#include <stdio.h>      
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//------------------------------------------------------------------

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

//------------------------------------------------------------------
size_t file_size        (FILE *stream);              

int count_lines         (char *buffer);

int text_read_to_buf    (Text *text, FILE *stream);

int string_alloc        (Text *text);

int text_fill_strings   (Text *text);

int text_print          (Text *text, FILE *output);

void text_ctor          (Text *text);

void text_dtor          (Text *text);

int text_read           (Text *text, FILE *fpin);
