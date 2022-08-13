#include "hamlet.h"
#include "../errors/errors.h"

int file_size(Text *text, FILE *stream)
{
    if (text == NULL) {
        return NULL_PTR;
    }
    if (stream == NULL) {
        return NULL_PTR;
    }
 
    int size = 0;

    if (fseek(stream, 0, SEEK_END)) {
        return FSEEK_ERROR;
    }

    size = ftell(stream);

    if (size == -1) {
        return FTELL_ERROR;
    }

    text->size = size;
    rewind(stream);

    return 0;
}

//------------------------------------------------------------------
int get_buffer_to_text(Text *text, FILE *stream) 
{
    if (text == NULL) {
        return NULL_PTR;
    }
    if (stream == NULL) {
        return NULL_PTR;
    }

    int size_ret = file_size(text, stream);
    if (size_ret) {
        return size_ret;
    }

    text->buffer = (char *) calloc(text->size + 1, sizeof(char));

    if (text->buffer == NULL) {
        return NO_MEMORY;
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
    if (text == NULL) {
        return NULL_PTR;
    }

    char *buffer = text->buffer;

    while ((buffer = strchr(buffer, '\n')) != NULL) {
        buffer++;
        text->nlines++;
    }
    
    return 0;
}

//------------------------------------------------------------------

int string_alloc(Text *text)
{
    if (text == NULL) {
        return NULL_PTR;
    }

    text->strings = (String *) calloc(text->nlines, sizeof(String));
    if (text->strings == NULL) {
        return NO_MEMORY;
    }

    return 0;
}

//------------------------------------------------------------------

int fill_strings_struct(Text *text)
{
    if (text == NULL) {
        return NULL_PTR;
    }

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

//------------------------------------------------------------------

int text_print_to_file(Text *text, FILE *output) 
{
    if (text == NULL) {
        return NULL_PTR;
    }
    if (output == NULL) {
        return F_CLOSE_ERROR;
    }

    String *cur_string = text->strings;

    for (int line_number = 0; line_number < text->nlines; line_number++) {
        fprintf(output,"%s\n",cur_string[line_number].string_ptr);
    }
    
    return 0;
}

//------------------------------------------------------------------

void struct_init(Text *text)
{
    text->nlines  = 0;
    text->size    = 0;
    text->buffer  = NULL;
    text->strings = NULL;
}

//------------------------------------------------------------------

int text_processing(FILE *stream)
{
    if (stream == NULL) {
        return F_OPEN_ERROR;
    }
    
    Text text;
    struct_init(&text);

    int get_buff_ret = get_buffer_to_text(&text, stream);
    if (get_buff_ret) {
        print_err_msg(get_buff_ret);
        return -1;
    }

    int count_lines_ret = count_lines(&text);
    if (count_lines_ret) {
        print_err_msg(count_lines_ret);
        return -1;
    }

    int str_alloc_ret = string_alloc(&text);
    if (str_alloc_ret) {
        print_err_msg(str_alloc_ret);
        return -1;
    }

    int fill_strings_ret = fill_strings_struct(&text);
    if (fill_strings_ret) {
        print_err_msg(fill_strings_ret);
        return -1;
    }





}

