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
char** tokens;
int forkIt();

int main() {
    welcomeMessage();
    char input[512]; //Allocates 512 bytes of null 0. Acts as eof
    printf("$> ");

    while (fgets(input, 512, stdin) != NULL){
        //Windows contingency
        if(strlen(input) == 1){
            printf("$> ");
            continue;
        }

        tokens = parsingTheLine(input);

        // if first token is "exit" then
        if(strcmp(tokens[0],"exit")==0 && tokens[1]==NULL)
            break;

        forkIt();

        printf("$> ");
    }

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
            printf("\n");
        }
    }
    return 0;
}