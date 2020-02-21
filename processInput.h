/**
 * Header file containing functions that deal with processing the input from user, such as:
 *  parsingTheLine - tokenization
 *  trimString - getting rid of trailing zeroes
 *  stringLength - getting the len of the string
 */

#include <stdlib.h>
#include <unistd.h>
#define TOKENIZERS " |><&;\t\n"


char** parsingTheLine(char*);
void setPath(char* directory);
void getPath();
void changeDirectory(char*);
int checkIfHistory(char* input);


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



void changeDirectory(char* nDirectory){
    int test = chdir(nDirectory);
    if (test ==-1)
        perror(nDirectory);
}

/**
 * method prints the current path
 */
void getPath(){
        printf("%s\n$>", getenv("PATH"));
    }

/**
 * method sets the current path
 */
void setPath(char* directory){
    setenv("PATH",directory,1);
    }

int checkIfHistory(char* input) {
    if (strcspn(input, "!") < strlen(input))
        return 1;
    else
        return 0;
}