/**
 * Header file containing functions that deal with processing the input from user, such as:
 *  parsingTheLine - tokenization
 *  trimString - getting rid of trailing zeroes
 *  stringLength - getting the len of the string
 */

#include <stdlib.h>

#define TOKENIZERS " |><&;\t"


int welcomeMessage();
int parsingTheLine(char*);
char* trimString(char*);
int stringLength(const char*);

/**
 * just a welcome message that shows up on the top of the shell
 * @return
 */
int welcomeMessage() {
    printf("Welcome to our Simple Shell!\n");
    return 1;
}

/**
 * breaking up the input
 * @param line to be split up
 * @return nothing so far (maybe write some check to see if was success?); or maybe it should return a pointer to that array?
 */

int parsingTheLine(char* input) {
    if (!strcmp(input, "exit"))
        return 0;

    int len = stringLength(input);
    char line[len];
    strcpy(line, input);

    char** tokens = malloc(512);
    int i = 0;
    char* token = strtok(line, TOKENIZERS);
    tokens[i] = token;

    while(token != NULL) {
        token = strtok(NULL, TOKENIZERS);
        i++;
        tokens[i] = token;
    }

    for (int j = 0; j < i; j++) {
        printf("\"%s\"\n", tokens[j]);
    }

    return 1;
}


/**
 * gets rid of the 0s/empty spaces that follow the string
 * @param line/input to be trimmed
 * @return trimmed line
 */

char* trimString(char* line) {
    int len = stringLength(line);
    line[len-1] = '\0';
    return line;
}

/**
 * @param line
 * @return length of the line
 */
int stringLength(const char* line) {
    int i = 0;
    while (line[i] != '\0') {
        i++;
    }
    return i;
}