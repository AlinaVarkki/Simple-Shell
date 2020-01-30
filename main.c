/** This is the main part of our C shell program
* group 11
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOKENIZERS " |><&;\t"

int welcomeMessage();
int parsingTheLine(char*);
char* trimString(char*);

int main() {
    welcomeMessage();
    char *input;

    while (strcmp(input, "exit")) {
        printf("$ ");
        fgets(input, 512, stdin);
        input = trimString(input);
        parsingTheLine(input);
     //   printf("%s\n", input);
    }

    return 1;
}


int welcomeMessage() {
    printf("Welcome to our Simple Shell!\n");
    return 1;
}

/**
 * breaking up the input
 * @param line to be split up
 * @return nothing so far (maybe write some check to see if was success?); or maybe it should return a pointer to that array?
 */

int parsingTheLine(char* line) {
    char** tokens = malloc(512);
    int i = 0;
    char* token = strtok(line, TOKENIZERS);
    tokens[i] = token;

    while(token != NULL) {
        token = strtok(NULL, TOKENIZERS);
        i++;
        tokens[i] = token;

    }

    printf("List of the tokens: ");
    printf("%s", tokens[0]);
    for (int j = 1; j < i; j++) {
        printf(", %s", tokens[j]);
    }
    printf("\n");
    return 1;
}


/**
 * gets rid of the 0s/empty spaces that follow the string
 * @param line/input to be trimmed
 * @return trimmed line
 */

char* trimString(char* line) {
    int i = 0;
    while (line[i] != '\0') {
        i++;
    }
    line[i-1] = '\0';
    return line;
}
