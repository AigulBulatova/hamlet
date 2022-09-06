#include "hamlet.h"
#include "../errors/errors.h"

#include <assert.h>

int file_size(Text *text, FILE *stream)      // return value = size
                                             // remove Text
{
    if (text == NULL || stream == NULL) {
        return NULL_PTR;
    }
 
    if (fseek(stream, 0, SEEK_END)) {
        return FSEEK_ERROR;
    }

    long size = ftell(stream);               //  выровнять
    if  (size == -1) {
        return FTELL_ERROR;
    }

    text->size = (size_t) size;
    rewind(stream);

    return 0;
}

//------------------------------------------------------------------

int get_buffer_to_text(Text *text, FILE *stream)               //text_read_to_buf 
{
    if (text == NULL) {
        // ERR_MSG("Null ptr to text structure")
        // return NULL_PTR:                                         // split err codes
    }
    if (stream == NULL) {
        return NULL_PTR;
    }

    int size_ret = file_size(text, stream);                      /// / / / /// / / / ///
    if (size_ret) {
        return size_ret;
    }

    text->buffer = (char *) calloc(text->size + 1, sizeof(char));
    if (text->buffer == NULL) {
        return NO_MEMORY;
    }

    size_t read = fread(text->buffer, sizeof(char), text->size, stream);
    if (read != text->size) {
        return -1;
    }
    text->buffer[text->size] = '\0';

    return 0;
}

// #ifdef LOGS

//  #define LOGS_MSG(...) logs_msg_print(__FILE__, ___LINE__, __FUNCTION__, __VA_ARGS__)

// #else

// #define LOGS_MSG(...) 

// #endif

// LOG_MSG("Allocated buffer address is %p", buffer);
// LOG_MSG("SIzeof of efemfem is %zd, sizeof(efemfem)");
// #define LOG_MSG(...) logs_msg_print(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
// log_msg_print()
//
// config.h #define LOGS
// 
// log_msg_print(...) -> stderr
//
// va_arg, vprintf, __VA_ARGS__
//
//  delete print_msg_err 
//
// ERR_MSG("Еуцалцуалу") -> вне зависимости от конфига
// #define ERR_MSG(msg_str) fprintf(stderr, "Error on line %d in file %s in func %s: %s", __LINE__,...)
//------------------------------------------------------------------

int count_lines(Text *text) //returning value is num of string, args: buffer
{
    if (text == NULL) {
        return NULL_PTR;
    }

    char *buffer = text->buffer;

    while ((buffer = strchr(buffer, '\n')) != NULL) {
        buffer++;
        text->nlines++;
    }
    text->nlines++;
    
    return 0;
}
 
//------------------------------------------------------------------

int string_alloc(Text *text)
{
    if (text == NULL) {
        // ERR_MSG("Text pointer is NULL"); -> 
        return NULL_PTR;
    }

    // fprintf(stderr, "text->nlines is %zd\n", (size_t)text->nlines);
    text->strings = (String *) calloc((size_t)text->nlines, sizeof(String));

    // printf("%ld\n", sizeof(text->strings));  // printf -> fprintf(stderr, ...)
    // printf("%d\n", text->nlines);
    // printf("%ld\n", sizeof(String));

    if (text->strings == NULL) {
        return NO_MEMORY;
    }

    return 0;
}

//------------------------------------------------------------------

int text_fill_strings(Text *text)
{
    if (text == NULL) {
        return NULL_PTR;
    }

    String *cur_struct = text->strings;
    char   *cur_string = text->buffer;

    for (int line_number = 0; line_number < text->nlines; line_number++) {
        fprintf(stderr, "cur number is %d\n", line_number);
        cur_struct[line_number].number = line_number;
        //printf("%d\n", cur_struct[line_number].number);
        cur_struct[line_number].string_ptr = cur_string;
        
        char *string_end = strchr(cur_string, '\n');

        *string_end = '\0';
        cur_struct[line_number].len = strlen(cur_string);

        cur_string = string_end + 1;
        //cur_struct++;
    }

    return 0;
}

//------------------------------------------------------------------

int text_print(Text *text, FILE *output) 
{
    if (text == NULL) {
        return NULL_PTR;
    }
    if (output == NULL) {
        //ERR_MSG("FILE* output is NULL in text_print");
        // return FILE_PTR_NULL_ERR;
        return F_OUTPUT_ERROR;
    }

    String *cur_string = text->strings;

    for (int line_number = 0; line_number < text->nlines; line_number++) {
        fprintf(output,"%s\n",cur_string[line_number].string_ptr);
    }
    
    return 0;
}

//------------------------------------------------------------------

void struct_init(Text *text) // -> text_ctor 
{
    text->nlines  = 0;
    text->size    = 0;
    text->buffer  = NULL;
    text->strings = NULL;
}

//------------------------------------------------------------------

int text_processing(FILE *stream)       // args: Text*, FILE* fpin
{
    if (stream == NULL) {
        return F_OPEN_ERROR;
    }
    
    Text text = {};
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
    FILE *result = fopen("result.txt", "r");

    int text_print_ret = text_print_to_file(&text, result);
    if(text_print_ret) {
        print_err_msg(text_print_ret);
        return -1;
    }

    fclose(result);       // -> close_file
    fclose(stream);      
    
    free(text.strings);  // -> dtor
    free(text.buffer);

    return 0;

}

