#include "errors.h"
#include "../general/general.h"
#include <stdarg.h>
#include <assert.h> 

//------------------------------------------------------------------

static FILE* log_file = NULL;
// open_log_file -> open_file
// close_log_file

int open_log_file ()
{
    log_file = open_file ("errors/log_file.txt", "w");
    if (log_file == NULL) {
        ERR_MSG ("Can not open log file.");
        return F_OPEN_ERR;
    }
    return 0;
}

//------------------------------------------------------------------

void print_log_message (const char *format, ...)
{
    assert (format);

    fprintf (log_file, "Log messade from file %s, line %d. \nFunction %s: ",
                         __FILE__, __LINE__, __FUNCTION__);

    va_list args = {};         
    va_start (args, format);
    vfprintf (log_file, format, args);
    va_end(args);

}

int close_log_file ()
{
    int close = close_file (log_file);
    if (close < 0) {
        return close;
    }
    
    return 0;
}

