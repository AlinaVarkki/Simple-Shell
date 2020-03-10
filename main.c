/**
 * This is the main part of our C shell program
 * group 11
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "processInput.h"
#include "fileManipulation.h"

#define SIZE_OF_HISTORY 20
#define DEBUG 0


int forkIt();
int returncommandIndex(char* command);
char** checkForInvocation(char**);

char** tokens;
int recurTemp;
char sysPath[500];
char directory[500];
char cwd[1000];
int commandNum = 0;
char* history[SIZE_OF_HISTORY];
char** tempHistory;
int historyCheck;


//list of our command to see if command entered is in the list
char *commands[] = {
        "exit",
        "setpath",
        "cd",
        "getpath",
        "alias",
        "unalias",
        "getpath",
        "history",
        "clearh",
        NULL
};

int main() {
    //saving the current path to restore it later
    strcpy(sysPath, getenv("PATH"));
    //setting current directory to home
    strcpy(directory, getenv("HOME"));
    chdir(directory);

    //saying what was the initial directory and what we changed it for
    printf("Initial path is %s \n", sysPath);
    getcwd(cwd, sizeof(cwd)); // using this to get the current directory(to make sure that it is home)
    printf("The directory is %s \n", cwd);


    printf("Loaded %d alias(es)\n",loadAliases());

    //gets history from a file
    tempHistory = loadHistory(&commandNum);
    int counter = 0;
    for (int i = 0; (i < commandNum && i < SIZE_OF_HISTORY); i++) {
        history[i] = tempHistory[i];
        counter += 1;
    }
    printf("Loading history from file, %d commands, current command %d (%d of %d):\n", counter, commandNum + 1,
           (commandNum + 1) % SIZE_OF_HISTORY, SIZE_OF_HISTORY);

    printf("\n+------------------------------+\n"
           "| Welcome to our Simple Shell! |\n"
           "+------------------------------+\n\n");

    char input[512]; //Allocates 512 bytes of null 0. Acts as eof
    printf("$> ");

    while (fgets(input, 512, stdin) != NULL) {
        //Windows contingency
        if (strlen(input) == 1) {
            printf("$> ");
            continue;
        }

        char** initialTokens;
        char *input2 = strdup(input);

        initialTokens = parsingTheLine(input);
        recurTemp = 0;
        tokens = checkForInvocation(initialTokens);
        if(checkHistory(initialTokens) == 1) {
            history[commandNum % SIZE_OF_HISTORY] = input2;
            commandNum += 1;
        }
        if(tokens == NULL){
            printf("$> ");
            continue;
        }

        // If debugging, print all tokens
        if (DEBUG) {
            int count = 0;
            printf("Listing tokens: \n");
            while (tokens[count] != NULL) {
                printf("%s\n", tokens[count]);
                count++;
            }
        }


        //if the method entered is not in the list of commands, execute else and forkit
        if (returncommandIndex(tokens[0]) > -1) {
            // if first token is "exit" then
            if (strcmp(tokens[0], "exit") == 0)
                if(tokens[1] == NULL) {
                    break;
                }
                else{
                    printf("The exit command does not accept any arguments\n");
                }

                //get current path
            else if (strcmp(tokens[0], "getpath") == 0){
                if(tokens[1] == NULL){
                    getPath();
                }
                else{
                    printf("The getpath command does not accept any arguments\n");
                }
            }

                //set path to whatever is asked
            else if (strcmp(tokens[0], "setpath") == 0) {
                if(tokens[1] != NULL && tokens[2] == NULL){
                    setPath(tokens[1]);
                }
                else{
                    printf("The setpath command takes 1 and only 1 argument : the path to be set\n");
                }
            }

                //changing the directory
            else if (strcmp(tokens[0], "cd") == 0) {
                if (tokens[1] == NULL) {
                    changeDirectory(directory);
                }
                else if(tokens[1] != NULL && tokens[2] == NULL) {
                    changeDirectory(tokens[1]);
                }
                else{
                    printf("The cd command takes at most 1 argument : the directory to go to\n");
                }
            } else if (strcmp(tokens[0], "alias") == 0) {
                if(tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL) {
                    aliasThis(tokens);
                }
                else if (tokens[1] == NULL) {
                    print_aliases();
                }
                else{
                    printf("The alias command accepts either 2 arguments to define an alias : The alias , the command attached to the alias\n");
                    printf("Or it takes no arguments to print currently defined aliases\n");
                }
            } else if (strcmp(tokens[0], "unalias") == 0 ) {
                if(tokens[1] != NULL && tokens[2] == NULL) {
                    unalias(tokens);
                }
                else{
                    printf("The unalias command takes only 1 argument : The alias to be deleted\n");
                }
            }  else if (strcmp(tokens[0], "history") == 0) {
                if(tokens[1] == NULL) {
                    printHistory(history, commandNum);
                }
                else{
                    printf("The history command takes no arguments\n");
                }
            } else if (strcmp(tokens[0], "clearh") == 0) {
                if(tokens[1] == NULL) {
                    commandNum = 0;
                    *history = NULL;
                }
                else{
                    printf("The clearh command takes no arguments\n");
                }
            }

                //invalid number of arguments for one of our pre-defined functions
            else {
                printf("Error: Invalid amount of arguments\n");
            }
        }
        else{
            if (historyCheck == 1) {
                forkIt(); }
        }
        printf("$> ");
    }



    //closing the shell
    strcpy(directory, getenv("HOME"));
    chdir(directory);

    if(alias_counter != 0) {
        int checkAlias = saveAliases();
        if (checkAlias != 1)
            printf("Alias save has failed.\n");
    }

    int checkHistory = saveHistory(history, commandNum);
    if (checkHistory != 1)
        printf("History save has failed.\n");

    //set the environment back to the original one
    setenv("PATH", sysPath, 1);
    printf("Path is restored to %s \n", sysPath);
    return 1;
}


int forkIt() {
    pid_t process_id, pid;
    int status;

    process_id = fork(); //Create the fork
    if (process_id == -1) {         //if fork failed
        printf("fork() failed\n");
        return -1;
    }
    if (process_id == 0) {      //if child executes
        execvp(tokens[0], tokens);
        perror(tokens[0]);
        exit(0);
    } else {
        pid = wait(&status);        //parent waits for change in status
        if (WIFEXITED(status)) {
            printf("");
        }
    }
    return 0;
}


//method that checks if the command is in the list of commands and returns negative value if it is not
int returncommandIndex(char* command){
    int i = 0;
    while(commands[i] != (char *)NULL)
    {
        if(strcmp(command, commands[i]) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

char** checkForInvocation(char** invoTokens){
    if(recurTemp> 10){
        printf("Overflow! Cannot run this command.\n");
        return NULL;
    }
    recurTemp++;

    //Check for aliases
    if (getAliasIndex(invoTokens[0]) > -1) {
        int pointer = getAliasIndex(invoTokens[0]);
        invoTokens[0] = strdup(aliases[pointer].command);

        int countInvoTokens = 1;
        while (invoTokens[countInvoTokens] != NULL)
            countInvoTokens++;
        countInvoTokens--;

        char **newInvoTokens = parsingTheLine(invoTokens[0]);

        int countInvoTokens2 = 0;
        while (newInvoTokens[countInvoTokens2] != NULL)
            countInvoTokens2++;

        char **finalInvoTokens = malloc(512);

        for (int i = 0; i < countInvoTokens2; i++)
            finalInvoTokens[i] = newInvoTokens[i];

        for (int i = countInvoTokens2; i < countInvoTokens + countInvoTokens2; i++)
            finalInvoTokens[i] = invoTokens[i - countInvoTokens2 + 1];

        invoTokens = finalInvoTokens;

        if (getAliasIndex(invoTokens[0]) > -1 || strcspn(invoTokens[0], "!") == 0){
            return checkForInvocation(invoTokens);
        }
        else{
            return invoTokens;
        }
    }
    else if (strcspn(invoTokens[0], "!") == 0) {
        char** invoTempTokens;
        historyCheck = -1;
        if (invoTokens[1] == NULL) {
            invoTempTokens = historyShenanigans(invoTokens, history, commandNum, &historyCheck);
            if (historyCheck == 1) {
                return NULL;
            }
        } else {
            printf("History invocations do not take any arguments\n");
            return NULL;
        }

        if (getAliasIndex(invoTempTokens[0]) > -1){
            return checkForInvocation(invoTokens);
        }
        else{
            return invoTempTokens;
        }
    }
    else{
        return invoTokens;
    }
}

