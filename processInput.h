/**
 * Header file containing functions that deal with processing the input from user, such as:
 *  parsingTheLine - tokenization
 *  trimString - getting rid of trailing zeroes
 *  stringLength - getting the len of the string
 */

#include <stdlib.h>
#include <unistd.h>

#define TOKENIZERS " |><&;\t\n"
#define SIZE_OF_HISTORY 20


char** parsingTheLine(char*);
void setPath(char* directory);
void getPath();
void changeDirectory(char*);
int checkIfHistory(char* input);
char** historyShenanigans(char**, char* history[20], int);
void printHistory(char* history[20], int);

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
    if (strcspn(input, "!") < strlen(input)) {
        return 1; }
    else {
        return 0; }
}

char** historyShenanigans(char** tokens, char* history[20], int commandNum) {
    if (strcspn(tokens[0],"!")==0){
        if (!strncmp(tokens[0],"!!",2)){
            if (commandNum != 0) {
                tokens = parsingTheLine(history[(commandNum - 1) % SIZE_OF_HISTORY]); }
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
            }
        }
        else if (!strncmp(tokens[0],"!-",2)){
            int number = (atoi(strtok(tokens[0],"!"))); //the number that has been passed in after !, negative
            if ((commandNum + number) > 0)
                tokens = parsingTheLine(history[(commandNum + number) % SIZE_OF_HISTORY]);
            else if (number ==0)
                printf("Error: That's some invalid input there, bro.\n");
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
            }
        }
        else{
            int number = (atoi(strtok(tokens[0],"!"))); //the number that has been passed in after !
            if (number < commandNum && number > 0)
                tokens = parsingTheLine(history[(number-1) % SIZE_OF_HISTORY]);
            else if (number ==0)
                printf("Error: That's some invalid input there, bro.\n");
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
            }
        }
    }
    return tokens;
}

void printHistory(char* history[20], int commandNum) {
    int index = 0;
    int curCommandNum = commandNum-1;
    if (curCommandNum<SIZE_OF_HISTORY) {
        while (index<SIZE_OF_HISTORY && index<(curCommandNum)) {
            if (history[index][strlen(history[index])-1] =='\n')
                printf("%d: %s",index+1,history[index]);
            else
                printf("%d: %s\n",index+1,history[index]);
            index=(index+1)%SIZE_OF_HISTORY;
        }
    }
    else {
        index = (curCommandNum+1)%SIZE_OF_HISTORY;
        for (int i=1; i<(SIZE_OF_HISTORY+1); i++){
            if (history[index][strlen(history[index])-1] =='\n')
                printf("%d: %s",i,history[index]);
            else
                printf("%d: %s\n",i,history[index]);
            index=(index+1)%SIZE_OF_HISTORY;
        }
    }
}
