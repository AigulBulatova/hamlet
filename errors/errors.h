#pragma once

//------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>

//------------------------------------------------------------------

#include "../configs.h"

//------------------------------------------------------------------

#ifdef LOGS

    #define log_message(...) print_log_message(__LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)

#else

    #define log_message(...)

#endif

#define ERR_MSG(msg_str) \
        fprintf(stderr, "Error on line %d in file %s in function %s: %s\n", __LINE__, __FILE__, __FUNCTION__, msg_str)

//------------------------------------------------------------------

enum Errors {          
    F_PTR_NULL_ERR   = -1,
    S_PTR_NULL_ERR   = -2,
    NO_MEMORY_ERR    = -3,
    F_OPEN_ERR       = -4,
    F_CLOSE_ERR      = -5,
    FSEEK_ERR        = -6,
    FTELL_ERR        = -7,
    FREAD_ERR        = -8,
    NULL_PTR_ERR     = -9
};

//------------------------------------------------------------------

void print_log_message (const unsigned int line, const char* file, const char* func, const char *format, ...);

int open_log_file  ();

int close_log_file ();
