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
void setPath(char* directory);
void getPath();

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
    tokens[i]=NULL;

    return tokens;
}

/**
 * mehod prints the current path
 */
void getPath(){
        printf(getenv("PATH"));}


/**
 * mehod sets the current path
 */
void setPath(char* directory){

    setenv("PATH",directory,1);
//        printf(chdir(directory));

}
