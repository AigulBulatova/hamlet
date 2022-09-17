#include <ctype.h>
#include "my_sort.h"
#include "../hamlet/hamlet.h"

//------------------------------------------------------------------

int straight_compare (const void *str1, const void *str2)
{
    assert (str1);
    assert (str2);

    const String *s1 = (const String*) str1;
    const String *s2 = (const String*) str2;

    const char *string1 = s1->string_ptr;
    const char *string2 = s2->string_ptr;
    //puts(string1);
    //puts(string2);

    int i = 0;
    int j = 0;

    while (string1[i] != '\0' || string2[j] != '\0') {
        //printf("%c %c\n", string1[i], string2[j]);
        if (!isalpha(string1[i])) {
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
        if (!isalpha(string2[j])) {
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

        int upper_c1 = toupper(string1[i]);
        int upper_c2 = toupper(string2[j]);
        //printf("%c %c\n", string1[i], string2[j]);

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

    int i = s1->len;
    int j = s2->len;  

    if (i == 0 || j == 0) {
        return j - i;
    }

    while (i >= 0 && j >= 0) {
        if (!isalpha(string1[i])) {
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
        if (!isalpha(string2[j])) {
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

        int upper_c1 = toupper(string1[i]);
        int upper_c2 = toupper(string2[j]);
        
        //printf("%c %c\n", string1[i], string2[j]);

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

//------------------------------------------------------------------

int my_sort (String *base, size_t number, int (*compare) (const void *str1, const void *str2))
{
    int left = 0;
    int right = number - 1;

    String *mid = base[number / 2];


}

//------------------------------------------------------------------

void my_swap (String *str1, String *str2)
{
    String *tmp = str1;

    str1 = str2;
    str2 = tmp;
}
