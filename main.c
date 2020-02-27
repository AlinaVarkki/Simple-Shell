/**
 * This is the main part of our C shell program
 * group 11
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "processInput.h"
#include "fileManipulation.h"

#define SIZE_OF_HISTORY 20
#define DEBUG 0



char** tokens;
int forkIt();
char path[500];
char directory[500];
char cwd[1000];
int commandNum = 0;
int returncommandIndex(char* command);
char* history[SIZE_OF_HISTORY];
char** tempHistory;
int historyCheck;




//list of our command to see if command entered is in the list
char *commands[] = {
        "exit",
        "setpath",
        "cd",
        "getpath",
        "alias", //if only "alises" is typed, it prints the list of aliases
        "unalias",
        "getpath",
        "history",
        "clearh",
        NULL
};

int main() {
    //saving the current path to restore it later
    strcpy(path, getenv("PATH"));
    //setting current directory to home
    strcpy(directory, getenv("HOME"));
    chdir(directory);

    //saying what was the initial directory and what we changed it for
    printf("Initial path is %s \n", path);
    getcwd(cwd, sizeof(cwd)); // using this to get the current directory(to make sure that it is home)
    printf("The directory is %s \n", cwd);


    printf("Loaded %d alias(es)\n",loadAliases());

    printf("Welcome to our Simple Shell!\n");
    //gets history from a file
    tempHistory = loadHistory(&commandNum);
    int counter = 0;
    for (int i = 0; (i < commandNum && i < SIZE_OF_HISTORY); i++) {
        history[i] = tempHistory[i];
        counter += 1;
    }
    printf("Loading history from file, %d commands, current command %d (%d of %d):\n", counter, commandNum + 1,
           (commandNum + 1) % SIZE_OF_HISTORY, SIZE_OF_HISTORY);
    //printHistory(history, commandNum+1);

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

        char *input2 = strdup(input);

        // Check for invoke from history commands
        //    if (checkIfHistory(input)) {
        tokens = parsingTheLine(input);



        historyCheck = 0;
        if (strcspn(tokens[0], "!") == 0) {

            if (tokens[1] == NULL) {
                tokens = historyShenanigans(parsingTheLine(input2), history, commandNum, &historyCheck);
                if (historyCheck == 1) {
                    printf("$> ");
                    continue;
                }
            } else {
                printf("Error: Invalid amount of arguments\n");
                printf("$> ");
                continue;
            }
        }
        else {
            history[commandNum % SIZE_OF_HISTORY] = strdup(input2);
            commandNum += 1;
        }


        //checking if the first token of the command is alias and if it is, change it to the real command

        if (getAliasIndex(tokens[0]) > -1) {
            int pointer = getAliasIndex(tokens[0]);
            tokens[0] = strdup(aliases[pointer].command);

            int countTokens = 1;
            while (tokens[countTokens] != NULL)
                countTokens++;
            countTokens--;

            char **newTokens = parsingTheLine(tokens[0]);

            int countTokens2 = 0;
            while (newTokens[countTokens2] != NULL)
                countTokens2++;

            char **finalTokens = malloc(512);

            for (int i = 0; i < countTokens2; i++)
                finalTokens[i] = newTokens[i];

            for (int i = countTokens2; i < countTokens + countTokens2; i++)
                finalTokens[i] = tokens[i - countTokens2 + 1];

            tokens = finalTokens;

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
                if (strcmp(tokens[0], "exit") == 0 && tokens[1] == NULL)
                    break;

                    //get current path
                else if (strcmp(tokens[0], "getpath") == 0 && tokens[1] == NULL) {
                    getPath();
                    continue;
                }

                    //set path to whatever is asked
                else if (strcmp(tokens[0], "setpath") == 0 && tokens[1] != NULL && tokens[2] == NULL) {
                    setPath(tokens[1]);
                }

                    //changing the directory
                else if (strcmp(tokens[0], "cd") == 0) {
                    if (tokens[1] == NULL) {
                        changeDirectory(directory);
                    } else {
                        changeDirectory(tokens[1]);
                    }
                } else if (strcmp(tokens[0], "alias") == 0 && tokens[1] != NULL && tokens[2] != NULL) {
                    aliasThis(tokens);
                } else if (strcmp(tokens[0], "unalias") == 0 && tokens[1] != NULL && tokens[2] == NULL) {
                    unalias(tokens);
                } else if (strcmp(tokens[0], "alias") == 0 && tokens[1] == NULL) {
                    print_aliases();
                } else if (strcmp(tokens[0], "history") == 0) {
                    printHistory(history, commandNum);
                } else if (strcmp(tokens[0], "clearh") == 0) {
                    commandNum = 0;
                    *history = NULL;
                }

                    //invalid number of arguments for one of our pre-defined functions
                else {
                    printf("Error: Invalid amount of arguments\n");
                }
            }
            else{
                forkIt();
            }
            printf("$> ");
        }



        //closing the shell
        strcpy(directory, getenv("HOME"));
        chdir(directory);

        if(alias_counter != 0) {
            int checkAlias = saveAliases();
            printf("Check if alias save is success: %d\n", checkAlias);
        }


        int checkHistory = saveHistory(history, commandNum);
        printf("Check if history save is success: %d\n", checkHistory);

        //set the environment back to the original one
        setenv("PATH", path, 1);
        printf("Path is restored to %s \n", path);
        return 1;
    }


    int forkIt() {
        pid_t process_id, pid; //Creates process id
        int status;

        process_id = fork(); //Create the fork
        if (process_id == -1) {         //if fork failed
            printf("fork() failed\n");
            return -1;
        }
        if (process_id == 0) {      //if child executes
            execvp(tokens[0], tokens);  //executes child process
            perror(tokens[0]);      //prints error from child if one exists
            exit(0);           // returns exit status
        } else {
            pid = wait(&status);        //parent waits for change in status
            if (WIFEXITED(status)) {      //separates prompt from error messages
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