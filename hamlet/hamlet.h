#pragma once

//------------------------------------------------------------------

#include <stdio.h>      
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//------------------------------------------------------------------

struct String { 
    int number = 0;
    size_t len = 0;

    char *string_ptr = nullptr;
};

struct Text {
    int nlines  = 0;
    size_t size = 0;

    char *buffer    = nullptr;
    String *strings = nullptr;
};

//------------------------------------------------------------------

long file_size        (FILE *stream);              

int count_lines         (char *buffer);

int text_read_to_buf    (Text *text, FILE *stream);

int string_alloc        (Text *text);

int text_fill_strings   (Text *text);

int text_print          (Text *text, FILE *output);

void text_ctor          (Text *text);

void text_dtor          (Text *text);

int text_read           (Text *text, FILE *fpin);
