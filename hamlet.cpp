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

int get_buffer_to_text(Hamlet *hamlet, FILE *stream) 
{
    assert(hamlet);
    assert(stream);

    hamlet->size = file_size(stream);
    hamlet->buffer = (char *) calloc(hamlet->size + 1, sizeof(char));

    if(!hamlet->buffer) {
        return -1;
    }

    int read = fread(hamlet->buffer, sizeof(char), hamlet->size, stream);
    if (read != hamlet->size) {
        return -1;
    }
    hamlet->buffer[hamlet->size] = '\0';

    return 0;
}

//------------------------------------------------------------------

int count_lines(Hamlet *hamlet)
{
    assert(hamlet);

    char *buffer = hamlet->buffer;

    while ((buffer = strchr(buffer, '\n')) != NULL) {
        buffer++;
        hamlet->nlines++;
    }
    
    return 0;
}

//------------------------------------------------------------------

int get_buffer_to_strings(Hamlet *hamlet, String *strings)
{
    assert(hamlet);
    assert(strings);

    hamlet->strings = (String *) calloc(hamlet->nlines, sizeof(String));
    if(hamlet->strings == NULL) {
        return -1;
    }

    return 0;
}

//------------------------------------------------------------------

int fill_strings_buffer(Hamlet *hamlet, String *strings)
{
    assert(hamlet);
    assert(strings);

    for (int line_number = 0; line_number < hamlet->nlines; line_number++) {
        hamlet->strings[line_number] ?????
    }
}