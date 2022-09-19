#include "errors.h"
#include "../general/general.h"
#include <stdarg.h>

//------------------------------------------------------------------

static FILE* log_file = NULL;

//------------------------------------------------------------------

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

void print_log_message (const unsigned int line, const char* file, const char* func, const char *format, ...)
{
    assert (format);
    assert (file);
    assert (func);

    fprintf (log_file, "Log messade from file %s, line %ud. Function %s: ",
                        file, line, func);

    va_list args = {}; 

    va_start (args, format);
    vfprintf (log_file, format, args);
    va_end (args);

    fprintf (log_file, "\n");
}

//------------------------------------------------------------------

int close_log_file ()
{
    int close = close_file (log_file);

    if (close < 0) {
        return close;
    }
    
    return 0;
}

