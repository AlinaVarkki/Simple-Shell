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
void aliasThis(char*);
int returncommandIndex(char* command);
int alias_counter = 0;
int getAliasIndex(char *target);

struct alias{
    char *name;
    char *command;
}aliases[10];



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

int getAliasIndex(char *target){
    if (target != NULL){
        for(int i=0; i < alias_counter; i++){
            if(strcmp(aliases[i].name, target) == 0){
                return i;
            }
        }
    }
    return -1;
};

/**
 * method to set an alias for a command
 */
void aliasThis(char* aliasNameAndCommand){
    int alIndex = getAliasIndex(aliasNameAndCommand[1]);
    //check if
    if(alias_counter >= 10){
        printf("You already have 10 aliases, no more can be added");
    }
    else if(alIndex == -1){
        pos = alias_counter;
        alias_counter++;

        //add to aliases at pos alias_counter
    }
    else {
        pos = alIndex;
    }
        //adding new alias
             int i = 1;

            while (aliasNameAndCommand[i] != NULL)
            {
                strcat(aliases[alIndex].command, aliasNameAndCommand[i]);
                strcat(aliases[alIndex].command," ");
                i++;
            }
    }
}



