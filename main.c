/** This is the main part of our C shell program
* group 11
*/

#include <stdio.h>
#include <string.h>

#include "processInput.h"

int main() {
    welcomeMessage();

    char *input;
    while (strcmp(input, "exit")) {
        printf("$> ");
        char* checkInput = fgets(input, 512, stdin);
        if (checkInput == NULL)
            break;
        trimString(input);
        parsingTheLine(input);
    }

    return 1;
}


