#include <stdio.h>
#include "hamlet/hamlet.h"

int main()
{
    FILE *hamlet = fopen("hamlet.txt", "r");
    text_processing(&hamlet);
    
}