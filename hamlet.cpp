#include "hamlet.h"

int file_size(FILE *stream)
{
    assert(stream);
 
    int size = 0;

    if (!fseek(stream, 0, SEEK_END)) {
        return -1;
    }

    size = ftell(stream);

    if(size == -1) {
        return -1;
    }

    return size;
}

//------------------------------------------------------------------
int get_buffer_to_text(Text *text, FILE *stream) 

{
    assert(text);
    assert(stream);

    text->size = file_size(stream);
    text->buffer = (char *) calloc(text->size + 1, sizeof(char));

    if(!text->buffer) {
        return -1;
    }

    int read = fread(text->buffer, sizeof(char), text->size, stream);
    if (read != text->size) {
        return -1;
    }
    text->buffer[text->size] = '\0';

    return 0;
}

//------------------------------------------------------------------

int count_lines(Text *text)
{
    assert(text);

    char *buffer = text->buffer;

    while ((buffer = strchr(buffer, '\n')) != NULL) {
        buffer++;
        text->nlines++;
    }
    
    return 0;
}

//------------------------------------------------------------------

int get_buffer_to_strings(Text *text)
{
    assert(text);

    text->strings = (String *) calloc(text->nlines, sizeof(String));
    if(text->strings == NULL) {
        return -1;
    }

    return 0;
}

//------------------------------------------------------------------

int fill_strings_struct(Text *text)
{
    assert(text);

    String *cur_struct = text->strings;
    char *cur_string = text->buffer;

    for (int line_number = 0; line_number < text->nlines; line_number++) {
        cur_struct[line_number].number = line_number;
        cur_struct[line_number].string_ptr = cur_string;
        
        char *string_end = strchr(cur_string, '\n');
        *string_end = '\0';
        cur_struct[line_number].len = strlen(cur_string);

        cur_string = string_end + 1;
        cur_struct++;
    }

    return 0;
}

int text_print_to_file(Text *text, FILE *output) 
{
    assert(text);
    assert(output);

    String *cur_string = text->strings;

    for (int line_number = 0; line_number < text->nlines; line_number++) {
        fputs(cur_string[line_number].string_ptr, output);
    }
    
    return 0;
}

