#pragma once

enum Errors {          //
    NULL_PTR_ERR   = -1,
    NO_MEMORY_ERR  = -2,
    F_OPEN_ERR     = -3,
    F_OUTPUT_ERR   = -4,
    FSEEK_ERR      = -5,
    FTELL_ERR      = -6,
};

int print_err_msg(int error);