#include "hamlet/hamlet.h"
#include "general/general.h"
#include "errors/errors.h"
#include "my_sort/my_sort.h"

// 2) sorting -> 1) qsort 2)your own qsort (config.h <- #define USE_MY_OWN_QSORT) 
// 3) comparator -> direct and reverse sort(.., comp)
// 4) number -> sort as it was <- comparator(number) (hint: dont use strcmp)
// 5) open_file, close_file <- errno, strerror 
// 6) argc, argv -> filename input, output

int main()
{
#ifdef LOGS 
    int logs = open_log_file ();
    if (logs < 0) return logs;
#endif

    FILE* fpin = open_file ("txt/hamlet.txt", "r");
    if (fpin == NULL) {
        ERR_MSG ("Can not open file");     
        return F_OPEN_ERR;
    }

    Text text = {};
    text_ctor (&text);

    int err = 0;
  
    err = text_read (&text, fpin);
    if (err < 0) return err;

    err = close_file (fpin);
    if (err < 0) return err;

//#ifdef USE_MY_SORT
    //my_sort();
//#else
    qsort (text.strings, text.nlines, sizeof(text.strings[0]), &straight_compare);
//#endif

    FILE* fpout = open_file ("txt/output.txt", "w");
    if (fpout == NULL) {
        ERR_MSG ("Can not open output file");
        return F_OPEN_ERR;
    }

    err = text_print (&text, fpout);
    if (err < 0) return err;

    err = close_file (fpout);
    if (err < 0) return err;

    int cmp = straight_compare (&text.strings[55], &text.strings[65]);
    printf("%d\n", cmp);

    text_dtor (&text);

    return 0;
}