#include <ctype.h>
#include "my_sort.h"
#include "../hamlet/hamlet.h"
#include "../configs.h"

//------------------------------------------------------------------

int direct_compare (const void *str1, const void *str2) 
{
    assert (str1);
    assert (str2);

    const String *s1 = (const String*) str1;
    const String *s2 = (const String*) str2;

    const char *string1 = s1->string_ptr;
    const char *string2 = s2->string_ptr;

    int i = 0;
    int j = 0;

    if (string1[i] == '\0' || string2[j] == '\0') {
        return string2[j] - string1[i];
    }

    while (string1[i] != '\0' || string2[j] != '\0') {
        if (!isalpha (string1[i])) {
            if (string1[i] == '\0' && string2[j] != '\0') {
            return 1;
            }
            else if(string1[i] == '\0') {
                break;
            }
            else {
            i++;
            continue;
            }
        }

        if (!isalpha (string2[j])) {
            if (string2[j] == '\0' && string1[i] != '\0') {
            return -1;
            }
            else if(string2[j] == '\0') {
                break;
            }
            else {
            j++;
            continue;
            }
        }

        int upper_c1 = toupper (string1[i]);
        int upper_c2 = toupper (string2[j]);

        if (upper_c1 != upper_c2) {
            return upper_c1 - upper_c2;
        }
        else {
            i++;
            j++;
        }
    }

    return 0;
}

//------------------------------------------------------------------

int reverse_compare (const void *str1, const void *str2)
{
    assert (str1);
    assert (str2);

    const String *s1 = (const String*) str1;
    const String *s2 = (const String*) str2;

    const char *string1 = s1->string_ptr;
    const char *string2 = s2->string_ptr;

    int i = (int) s1->len;
    int j = (int) s2->len;  

    if (i == 0 || j == 0) {
        return j - i;
    }

    while (i >= 0 && j >= 0) {
        if (!isalpha (string1[i])) {
            if (i < 0 && j >= 0) {
                return 1;
            }
            else if (i < 0) {
                break;
            }
            else {
                i--;
                continue;
            }
        }

        if (!isalpha (string2[j])) {
            if (j < 0 && i >= 0) {
                return -1;
            }
            else if (j < 0) {
                break;
            }
            else {
                j--;
                continue;
            }
        }

        int upper_c1 = toupper (string1[i]);
        int upper_c2 = toupper (string2[j]);

        if (upper_c1 != upper_c2) {
            return upper_c1 - upper_c2;
        }
        else {
            i--;
            j--;
        }
    }

    return 0;
}

int text_sort_and_print (Text *text, FILE *direct, FILE *reverse)
{
    #ifdef USE_MY_SORT
        my_qsort (text->strings, text->nlines,sizeof(text->strings[0]), &direct_compare);
    #else
        qsort (text->strings, (size_t) text->nlines, sizeof(text->strings[0]), &direct_compare);
    #endif

        int print = text_print (text, direct);
        if (print < 0) return print;

    #ifdef USE_MY_SORT
        my_qsort (text->strings, text->nlines,sizeof(text->strings[0]), &reverse_compare);
    #else
        qsort (text->strings, (size_t) text->nlines, sizeof(text->strings[0]), &reverse_compare);
    #endif

        print = text_print (text, reverse);
        if (print < 0) return print;
    
    return 0;
}

//------------------------------------------------------------------

long my_partition (char* base, long left, long right, long size, int (*compare) (const void*, const void*)) {

	char* pivot = base + right;
	long i = left - size;

	for (long j = left; j <= right - size; j += size) {

		if (compare ((const void*) (base + j), (const void*) pivot) < 0) {

			i += size;
			swap (base + i, base + j, (size_t) size);
		}
	}
	swap (base + i + size, base + right, (size_t) size);
	return (i + size);
}

//------------------------------------------------------------------

void my_qsort (void *base_el, long n, long size, int (*cmp) (const void* , const void* )) 
{

	char* base = (char*) base_el;
	long left = 0;
	long right = size * (n - 1);

	if (n < 2) return;

	long pi = my_partition (base, left, right, size, cmp);

	my_qsort ((void*)base, (pi - left)/size, size, cmp);
	my_qsort ((void*)(base + pi + size), (right - pi)/size, size, cmp);
}

//------------------------------------------------------------------

void swap (char* first, char* second, size_t size) {         

	assert (first != NULL);
	assert (second != NULL);

	char* temp = (char*) calloc (1, size);
	assert (temp != NULL);

	memcpy (temp, first, size);
	memcpy (first, second, size);
	memcpy (second, temp, size);

	free (temp);
}
