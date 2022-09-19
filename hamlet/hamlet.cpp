#include "hamlet.h"
#include "../errors/errors.h"
#include "../configs.h"

//------------------------------------------------------------------

long file_size (FILE *stream)                 
{
    if (stream == NULL) {
        ERR_MSG ("File  pointer is NULL");
        return F_PTR_NULL_ERR;
    }
 
    if (fseek (stream, 0, SEEK_END)) {
        ERR_MSG ("Fseek error");
        return FSEEK_ERR;
    }

    long size = ftell (stream);            
    if  (size == -1) {
        ERR_MSG ("Ftell error");
        return FTELL_ERR;
    }

    rewind (stream);

    return size;
}

//------------------------------------------------------------------

int text_read_to_buf (Text *text, FILE *stream)               
{
    if (stream == NULL) {
        ERR_MSG ("File  pointer is NULL");
        return F_PTR_NULL_ERR;                                        
    }
    if (text == NULL) {
        ERR_MSG ("Text pointer is NULL"); 
        return S_PTR_NULL_ERR;                                        
    }

    long size = file_size (stream);
    if (size < 0) {
        return (int) size;
    }                 
    text->size = (size_t) size;

    text->buffer = (char *) calloc (text->size + 1, sizeof(char));
    log_message ("Allocated text buffer address is %p\n", text->buffer);

    if (text->buffer == NULL) {
        ERR_MSG ("Can not allocate memory");
        return NO_MEMORY_ERR;
    }

    size_t read = fread (text->buffer, sizeof(char), text->size, stream);
    log_message ("%d symbols read by fread(). Size of the text is %d\n", read, text->size);

    if (read != text->size) {
        ERR_MSG ("Fread error");
        return FREAD_ERR;
    }
    text->buffer[text->size] = '\0';

    return 0;
}

//------------------------------------------------------------------

int count_lines (char *buffer)
{
    if (buffer == NULL) {
        ERR_MSG ("Buffer pointer is NULL");
        return NULL_PTR_ERR;
    }

    int nlines = 0;

    while ((buffer = strchr (buffer, '\n')) != NULL) {
        buffer++;
        nlines++;
    }             

    log_message ("Number of lines is %d\n", nlines);                  
    
    return nlines;
}
 
//------------------------------------------------------------------ 

int string_alloc (Text *text)
{
    if (text == NULL) {
        ERR_MSG ("Text pointer is NULL");  
        return S_PTR_NULL_ERR;
    }

    int nlines = count_lines (text->buffer);
    if (nlines < 0)
        return nlines;
    
    text->nlines = nlines;

    text->strings = (String *) calloc ((size_t)text->nlines, sizeof(String));
    log_message ("Allocated array of strings address is %p\n", text->strings);
    
    if (text->strings == NULL) {
        ERR_MSG ("Can not allocate memory");
        return NO_MEMORY_ERR;
    }

    return 0;
}

//------------------------------------------------------------------

int text_fill_strings (Text *text)
{
    if (text == NULL) {
        ERR_MSG ("Text pointer is NULL"); 
        return S_PTR_NULL_ERR;
    }

    String *cur_string = text->strings;
    char   *string_start = text->buffer;

    for (int line_number = 0; line_number < text->nlines ; line_number++) {
        cur_string[line_number].number = line_number;           
        cur_string[line_number].string_ptr = string_start; 

        char *end = strchr (string_start, '\r');
        char *n = strchr (string_start, '\n');

        *end = '\0';
        *n = '\0';
        if (!n) break;

        cur_string[line_number].len = strlen (string_start);

        string_start = n + 1;
    }

    return 0;
}

//------------------------------------------------------------------

int text_print (Text *text, FILE *output) 
{
    assert (output);
    assert (text);

    String *cur_string = text->strings;

    for (int line_number = 0; line_number < text->nlines; line_number++) {
        fprintf (output,"%s\n", cur_string[line_number].string_ptr);
    }
    
    return 0;
}

//------------------------------------------------------------------

void text_ctor (Text *text)  
{
    assert (text);

    text->nlines  = 0;
    text->size    = 0;
    text->buffer  = NULL;
    text->strings = NULL;
}

//------------------------------------------------------------------

void text_dtor (Text *text)
{
    assert (text);

    free (text->buffer);
    free (text->strings);
}

//------------------------------------------------------------------

int text_read (Text *text, FILE *fpin)       
{
    if (fpin == NULL) {
        return F_PTR_NULL_ERR;
    }
    if (text == NULL) {
        return S_PTR_NULL_ERR;
    }

    int read_to_buff_ret = text_read_to_buf (text, fpin);
    if (read_to_buff_ret < 0) {
        return read_to_buff_ret;
    }

    int str_alloc_ret = string_alloc (text);
    if (str_alloc_ret) {
        return str_alloc_ret;
    }

    int fill_strings_ret = text_fill_strings (text);
    if (fill_strings_ret) {
        return fill_strings_ret;
    }

    return 0;
}

