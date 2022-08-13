#include "errors.h"

int print_err_msg(int error)
{
    switch (error) {
        case NULL_PTR: {
            printf("Null pointer of file or structure.\n");
            break;
        }
        case NO_MEMORY: {
            printf("Can not find free memory.\n");
            break;
        }
        case F_OPEN_ERROR: {
            printf("Can not open the file.\n");
            break;
        }
        default: {
            
        }
    }
}