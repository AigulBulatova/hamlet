#include "general.h"
#include "../errors/errors.h"

//------------------------------------------------------------------

FILE *open_file (const char *filename, const char *mode)
{
    if (filename == NULL) {
        ERR_MSG ("Null pointer to filename");
        return NULL;
    }
    if (mode == NULL) {
        ERR_MSG ("Null pointer to file mode");
        return NULL;
    }

    FILE *fp = fopen (filename, mode);

    return fp;
}

//------------------------------------------------------------------

int close_file (FILE *fileptr)
{
    if (fileptr == NULL) {
        ERR_MSG ("Null pointer to file");
        return F_PTR_NULL_ERR;
    }

    int close = fclose (fileptr);
    if (close == EOF) {
        ERR_MSG ("Can not close the file");
        return F_CLOSE_ERR;
    }

    return 0;
}
