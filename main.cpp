#include "hamlet/hamlet.h"
#include "general/general.h"
#include "errors/errors.h"
#include "my_sort/my_sort.h"
#include "configs.h"

int main()
{
    int err = 0;

    #ifdef LOGS 
        
        err = open_log_file ();
        if (err < 0) return err;
    
    #endif

    FILE *fpin = open_file ("txt/hamlet.txt", "r");
    if (fpin == NULL) {
        ERR_MSG ("Can not open text file");     
        return F_OPEN_ERR;
    }

    Text text = {};
    text_ctor (&text);
  
    err = text_read (&text, fpin);
    if (err < 0) return err;

    err = close_file (fpin);
    if (err < 0) return err;

    FILE *fpdir = open_file ("txt/direct_sorted.txt", "w");
    if (fpdir == NULL) {
        ERR_MSG ("Can not open output file");
        return F_OPEN_ERR;
    }

    FILE *fprev = open_file ("txt/reverse_sorted.txt", "w");
    if (fprev == NULL) {
        ERR_MSG ("Can not open output file");
        return F_OPEN_ERR;
    }

    err = text_sort_and_print (&text, fpdir, fprev);
    if (err < 0) return err;

    err = close_file (fpdir);
    if (err < 0) return err;

    err = close_file (fprev);
    if (err < 0) return err;

    text_dtor (&text);

    #ifdef LOGS

        err = close_log_file();
        if (err < 0) return err;

    #endif

    return 0;
}