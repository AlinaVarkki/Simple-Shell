/**
 * Header file containing functions that deal with processing the input from user, such as:
 *  parsingTheLine - tokenization
 *  trimString - getting rid of trailing zeroes
 *  stringLength - getting the len of the string
 */

#include <stdlib.h>

#define TOKENIZERS " |><&;\t\n"


int welcomeMessage();
char** parsingTheLine(char*);
char* trimString(char*);
int stringLength(const char*);



/**
 * breaking up the input
 * @param line to be split up
 * @return nothing so far (maybe write some check to see if was success?); or maybe it should return a pointer to that array?
 */

char** parsingTheLine(char* input) {

    char** tokens = malloc(512);
    int i = 0;
    char* token = strtok(input, TOKENIZERS); //puts first token into token

    // Adds individual tokens into token array
    while(token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, TOKENIZERS);
    }

    return tokens;
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
