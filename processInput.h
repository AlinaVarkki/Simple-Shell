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
void aliasThis(char**);
int returncommandIndex(char* command);
int alias_counter = 0;
int getAliasIndex(char *target);
void unalias(char**);

struct alias{
    char *name;
    char *command;
}aliases[10];


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

char** historyShenanigans(char** tokens, char* history[SIZE_OF_HISTORY], int commandNum) {
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
            if ((commandNum + number) > commandNum - SIZE_OF_HISTORY)
                tokens = parsingTheLine(history[(commandNum + number) % SIZE_OF_HISTORY]);
            else if (number == 0)
                printf("Error: That's some invalid input there, bro.\n");
            else {
                printf("Error: Can't go that far back into history, sorry bud.\n");
            }
        }
        else{
            int number = (atoi(strtok(tokens[0],"!"))); //the number that has been passed in after !
            if (number < commandNum && number > commandNum - SIZE_OF_HISTORY)
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
                printf("%d: %s",commandNum - SIZE_OF_HISTORY + i,history[index]);
            else
                printf("%d: %s\n",commandNum - SIZE_OF_HISTORY + i,history[index]);
            index=(index+1)%SIZE_OF_HISTORY;
        }
    }
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
void aliasThis(char** aliasNameAndCommand){
    int alIndex = getAliasIndex(aliasNameAndCommand[1]);

    //line checks what index does the command have
    //not needed until testinga
    //printf("Index: %d\n",alIndex);


    if(alias_counter >= 10){
        printf("You already have 10 aliases, no more can be added");
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
        while (aliasNameAndCommand[i] != NULL)
        {
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

        //adding new alias
        int i = 2;

        aliases[position].name = strdup (aliasNameAndCommand[1]);
        aliases[position].command = strdup(aliasNameAndCommand[i++]);
        while (aliasNameAndCommand[i] != NULL) {
            strcat(aliases[alIndex].command, aliasNameAndCommand[i]);
            strcat(aliases[alIndex].command, " ");
            i++;
        }
    }
}

//remove alias from the list
void unalias(char** aliasNameAndCommand)
{
    int pointer = getAliasIndex(aliasNameAndCommand[1]);

        //if alias exists pointer will return its' position in the array

        //remove alias from array
        if (pointer >= 0)
        {

            for (int i = pointer + 1; i < alias_counter; i++)
            {
                strcpy(aliases[i - 1].name, aliases[i].name);
                strcpy(aliases[i - 1].command, aliases[i].command);
            }

            //decrement alias count
            alias_counter--;
        }
        else
        {
            printf("Error: Alias %s does not exist.\n", aliasNameAndCommand[1]);
        }

}


//print the list of aliases
void print_aliases()
{
    int i = 0;
    if (alias_counter == 0)
    {
        printf("You don't have any aliases set\n");
    }
    while (i < alias_counter)
    {
        printf("%d %s : %s\n", (i+1),aliases[i].name, aliases[i].command);
        i++;
    }
}
