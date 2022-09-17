#include <ctype.h>
#include "my_sort.h"
#include "../hamlet/hamlet.h"

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

        /*if (isupper(string1[i]) && isupper(string2[j]) ||
            islower(string1[i]) && islower(string2[j])) {
                
            //printf("%c %c\n", string1[i], string2[j]);
            if (string1[i] != string2[j]) {
                return (string1[i] - string2[j]);
            }
            else {
                i++;
                j++;
            }
        }

        else if (isupper(string1[i]) && islower(string2[j])) {
            //printf("%c %c\n", string1[i], string2[j]);
            if ((string1[i] - 'A') != (string2[j] - 'a')) {
                return ((string1[i] - 'A') - (string2[j] - 'a'));
            }
            else {
                i++;
                j++;
            }
        }
        
        else {
            //printf("%c %c\n", string1[i], string2[j]);
            if ((string1[i] - 'a') != (string2[j] - 'A')) {
                return ((string1[i] - 'a') - (string2[j] - 'A'));
            }
            else {
                i++;
                j++;
            }
        }*/
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

    size_t len1 = s1->len;
    size_t len2 = s2->len;                      // 0 1 2 3 4 5 6 7 8 9 10
                                                // h e l l o w o r l d \0
    printf("%s\n", string1);
    printf("%s\n", string2);

    int i = len1 - 1;
    int j = len2 - 1;

    while (i > 0 || j > 0) {
        if (!isalpha(string1[i])) {                   //'\0'
            i--;
            continue;
        }
        if (!isalpha(string2[j])) {
            j--;
            continue;
        }


    }


}

//int my_sort (void *base, size_t num, size_t size, int (*compare) (const void *str1, const void *str2))
