#include <stdio.h>
#include "hamlet.h"

int main()
{
    Text hamlet;
    FILE *file = fopen("hamlet.txt", "r");
    get_buffer_to_text(&hamlet, file);
    count_lines(&hamlet);
    get_buffer_to_strings(&hamlet);
    fill_strings_struct(&hamlet);
    FILE *out = fopen("result.txt", "w");
    text_print_to_file(&hamlet, out);
    fclose(out);
    fclose(file);
    
}