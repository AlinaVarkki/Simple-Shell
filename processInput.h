/**
 * Header file containing functions that deal with processing the input from user
 */

#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define TOKENIZERS " |><&;\t\n"
#define SIZE_OF_HISTORY 20


char** parsingTheLine(char*);
void setPath(char* directory);
void getPath();
void changeDirectory(char*);
int checkHistory(char**);
char** historyShenanigans(char**, char* history[20], int, int*);
void aliasThis(char**);
int getAliasIndex(char *target);
void unalias(char** );
void printHistory(char* history[20], int);

int alias_counter = 0;

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


/**
 * changes the directory
 * @param nDirectory
 */
void changeDirectory(char* nDirectory){
    int test = chdir(nDirectory);
    if (test ==-1)
        perror(nDirectory);
}

/**
 * method prints the current path
 */
void getPath(){
    printf("%s\n", getenv("PATH"));
}

/**
 * method sets the current path
 */
void setPath(char* directory){
    setenv("PATH",directory,1);
}

/**
 * checks if the input is a history invocation
 * @param tokens
 * @return 1 if hisotry invocation is well-formed, 0 otherwise
 */
int checkHistory(char** tokens) {
    int count = 0;
    int dashCount = 0;

    if(tokens[0][0] != '!'){
        return 1;
    }

    while(tokens[0][count] != (char)NULL){
        if(tokens[0][count] == '-'){
            dashCount++;
            if(dashCount > 1 || count != 1){
                return 1;
            }
        }
        if(count>1 && tokens[0][count] == '!'){
            return 1;
        }
        count++;
    }
    count = 0;

    if(strtok(tokens[0],"!-") == NULL){
        if(strcmp(tokens[0],"!!") == 0){
            return 0;
        }
        else
            return 1;
    }

    while(strtok(tokens[0],"!-")[count] != (char)NULL){
        if (!isdigit(strtok(tokens[0],"!-")[count])){
            return 1;
        }
        count++;
    }
    return 0;
}


/**
 * switches out history invocation for the actual command that's to be executed
 * @param tokens
 * @param history
 * @param commandNum
 * @param historyCheck
 * @return tokens with the commands to be executed
 */
char** historyShenanigans(char** tokens, char* history[20], int commandNum, int *historyCheck) {
    *historyCheck = checkHistory(tokens);
    if(*historyCheck == 1){
        printf("Error: Please enter a number!\n");
        return NULL;
    }
    if (strcspn(tokens[0],"!")==0 && strlen(tokens[0]) >1){
        if (!strncmp(tokens[0],"!!",2)){
            if (commandNum != 0) {
                tokens = parsingTheLine(strdup(history[(commandNum - 1) % SIZE_OF_HISTORY])); }
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
                *historyCheck =1;
            }
        }
        else if (!strncmp(tokens[0],"!-",2)){
            int number = (atoi(strtok(tokens[0],"!"))); //the number that has been passed in after !, negative
            if ((number * -1) <= SIZE_OF_HISTORY)  //(commandNum + 1 + number) > 0 &&
                tokens = parsingTheLine(strdup(history[(commandNum + number) % SIZE_OF_HISTORY]));
            else if (number == 0) {
                printf("Error: That's some invalid input there, bro.\n");
                *historyCheck =1; }
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
                *historyCheck =1;
            }
        }
        else {
            int number = (atoi(strtok(tokens[0], "!"))); //the number that has been passed in after !
            if (number > 0 && number <= SIZE_OF_HISTORY){
                if (commandNum <= SIZE_OF_HISTORY) {
                    tokens = parsingTheLine(strdup(history[(number) - 1]));
                }
                else {
                    tokens = parsingTheLine(strdup(history[(commandNum - (SIZE_OF_HISTORY - number)) % SIZE_OF_HISTORY - 1]));
                }
            }
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
                *historyCheck =1;
            }
        }
    }
    return tokens;
}

/**
 * prints out the history
 * @param history
 * @param commandNum
 */
void printHistory(char* history[20], int commandNum) {
    int index = 0;
    int curCommandNum = commandNum-1;
    if (curCommandNum<SIZE_OF_HISTORY) {
        while (index<SIZE_OF_HISTORY && index<(curCommandNum+1)) {
            if (history[index][strlen(history[index])-1] =='\n')
                printf("%d: %s",index+1,history[index]);
            else
                printf("%d: %s\n",index+1,history[index]);
            index=(index+1);
        }
    }
    else {
        index = (curCommandNum+1)%SIZE_OF_HISTORY;
        for (int i=1; i<(SIZE_OF_HISTORY+1); i++){
            if (history[index][strlen(history[index])-1] =='\n')
                printf("%d: %s", i,history[index]);
            else
                printf("%d: %s\n", i,history[index]);
            index=(index+1)%SIZE_OF_HISTORY;
        }
    }
}

/**
 * gets alias index
 * @param target
 * @return
 */
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
 * @param aliasNameAndCommand
 */
void aliasThis(char** aliasNameAndCommand){
    int alIndex = getAliasIndex(aliasNameAndCommand[1]);

    if(alias_counter >= 10 && alIndex == -1){
        printf("You already have 10 aliases, no more can be added\n");
        return;
    }
    //case when the alias doesn't yet exist and is added to the array
    //getAliasIndex returns -1 if it doesn't find the alias in the array of aliases
    if(alIndex == -1){
        int position = alias_counter;
        //i starts from 1 because we don't need to consider the called command itself "alias"
        int i = 2;
        aliases[position].name = strdup (aliasNameAndCommand[1]);
        aliases[position].command = strdup(aliasNameAndCommand[i++]);
        while (aliasNameAndCommand[i] != NULL){
            strcat(aliases[position].command," ");
            strcat(aliases[position].command, aliasNameAndCommand[i]);
            i++;
        }
        //add to aliases at pos alias_counter
        alias_counter++;
    }
    //case when the alias already exists and is just updated
    else {
        int position = alIndex;
        printf("Overwriting alias on %s\n", aliases[alIndex].name);
        //adding new alias
        int i = 2;
        aliases[position].command = strdup("");
        while (aliasNameAndCommand[i] != NULL) {
            strcat(aliases[alIndex].command, aliasNameAndCommand[i]);
            strcat(aliases[alIndex].command, " ");
            i++;
        }
    }
}


/**
 * remove alias from the list
 * @param aliasNameAndCommand
 */
void unalias(char** aliasNameAndCommand) {
    int pointer = getAliasIndex(aliasNameAndCommand[1]);
        //if alias exists pointer will return its' position in the array

        //remove alias from array
        if (pointer >= 0) {
            for (int i = pointer + 1; i < alias_counter; i++) {
                strcpy(aliases[i - 1].name, aliases[i].name);
                strcpy(aliases[i - 1].command, aliases[i].command);
            }
            //decrement alias count
            alias_counter--;
        }
        else {
            printf("Error: Alias %s does not exist.\n", aliasNameAndCommand[1]);
        }
}


/**
 * prints out the list of aliases
 */
void print_aliases() {
    int i = 0;
    if (alias_counter == 0){
        printf("You don't have any aliases set\n");
    }
    while (i < alias_counter) {
        printf("%d %s : %s\n", (i+1),aliases[i].name, aliases[i].command);
        i++;
    }
}


