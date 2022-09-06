#include <stdio.h>
#include "hamlet/hamlet.h"

int main()
{
    FILE *hamlet = fopen("txt/hamlet.txt", "r");
    text_processing(hamlet);                       // -> 
    return 0;
    
    // Text text= { 0 };

    // hamlet_ctor, dtor, ...

    // hamlet_free

    //------------------------

    // FILE* fpin = fopen("txt/hamlet.txt", "r");
    // if (!fpin) 
            // print_err_msg
    //     return FOPEN_ERR;

    // Text text = {};

    // text_ctor(&text);

    // int err = 0;

    // err = text_read(&text, fpin);
    // if (err < 0)
    //      return err;

    // int err = fclose(fpin);
    // if ....

    // sorting

    // FILE* fpout = fopen("txt/output.txt", "w");
    // if (!fpout)
    //      return FOPEN_ERR;

    // err = text_print(&text, fpout);
    // if ...

    // err = fclose(fpout);
    // if ....

    // err = text_dtor(&text);
    // if (err < 0)
    //    return err;

    // return 0;
}