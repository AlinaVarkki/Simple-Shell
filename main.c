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

#define SIZE_OF_HISTORY 20

#include "fileManipulation.h"

char** tokens;
int forkIt();
char path[500];
char directory[500];
char cwd[1000];
int commandNum = 0;
int returncommandIndex(char* command);
char* history[SIZE_OF_HISTORY];
char** tempHistory;

//list of our command to see if command entered is in the list
char *commands[] = {
        "exit",
        "setpath",
        "cd",
        "getpath",
        "history"
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

    //gets history from a file
   // char** tempHistory = malloc(512);
     tempHistory = loadHistory(&commandNum);
    printf("%d\n", commandNum);
    for(int i=0; i<commandNum; i++) {
        printf("tempHistory[%d] = %s\n", i+1, tempHistory[i]);
        history[i] = tempHistory[i]; }
  //  free(tempHistory);
//    printf("Loading history from file, n of commands: %d, history:\n", commandNum);
//    printHistory(history, commandNum);



    printf("Welcome to our Simple Shell!\n");

    char input[512]; //Allocates 512 bytes of null 0. Acts as eof
    printf("$>");

    while (fgets(input, 512, stdin) != NULL){
        //Windows contingency
        if(strlen(input) == 1){
            printf("$>");
            continue;
        }

        // Check for invoke from history commands
        if (checkIfHistory(input)) {
            tokens = parsingTheLine(input);
            if (strcspn(tokens[0],"!")==0)
                tokens = historyShenanigans(parsingTheLine(input), history, commandNum);
            else {
                history[commandNum % SIZE_OF_HISTORY] = strdup(input);
                tokens = parsingTheLine(input);
                commandNum += 1;
            }
        }
        else{
            // Save as new history and run
            history[commandNum % SIZE_OF_HISTORY] = strdup(input);
            tokens = parsingTheLine(input);
            commandNum += 1;
        }

        //if the method entered is not in the list of commands, execute else and forkit
        if(returncommandIndex(tokens[0]) > -1) {
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
            else if (strcmp(tokens[0],"cd")== 0){
                if(tokens[1] == NULL){
                    changeDirectory(directory);
                }
                else{
                    changeDirectory(tokens[1]);
                }
            }

            //prints out history
            else if(strcmp(tokens[0],"history") == 0){
                printHistory(history, commandNum);
                }

            //invalid number of arguments for one of our pre-defined functions
            else {
                printf("Error: Invalid invalid amount of arguments\n");
            }

        }
        else {
            forkIt();
        }
        printf("$> ");
    }

    //closing the shell
    int check = saveHistory(history, commandNum);
    printf("Check if history save is success: %d\n", check);

    //set the environment back to the original one
    setenv("PATH", path,1);
    printf("Path is restored to %s \n", path);

    return 1;
}

int forkIt () {
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
    }
    else {
        pid = wait(&status);        //parent waits for change in status
        if(WIFEXITED(status)){      //separates prompt from error messages
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