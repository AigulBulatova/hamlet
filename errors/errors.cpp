#include "errors.h"
#include <stdio.h>

int print_err_msg(int error) // + __FILE__ __LINE__ __FUNCTION__ -> define

// PRINT_ERR_MSG(FOPEN_ERR) -> print_err_msg(FOPEN_ERR, __FILE__, ...)

{
    switch (error) {
        case NULL_PTR: {
            printf("Null pointer of file or structure.\n"); // -> fprintf(stderr, ...)
            break;
        }
        case NO_MEMORY: {
            printf("Can not allocate memory.\n");
            break;
        }
        case F_OPEN_ERROR: {
            printf("Can not open the file.\n");
            break;
        }
        case F_OUTPUT_ERROR: {
            printf("Can not open output file.\n");
            break;
        }
        case FSEEK_ERROR: {
            printf("Error in fseek()\n");
            break;
        }
        default: {
            // fprintf(stderr, "Unexpected error code.");
        }
    }
    return 0;
}

