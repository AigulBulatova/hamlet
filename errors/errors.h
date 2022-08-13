#pragma once

enum errors {
    NULL_PTR = 1,
    NO_MEMORY = -2,
    F_OPEN_ERROR = 3,
    F_CLOSE_ERROR = 4,
    FSEEK_ERROR,
    FTELL_ERROR
    
};

int print_err_msg(int error);