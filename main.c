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
    char input[512];
    printf("$> ");

    while (fgets(input, 512, stdin) != NULL){

        if(strlen(input) == 1){
            printf("$> ");
            continue;
        }

        tokens = parsingTheLine(input);

        if(strcmp(tokens[0],"exit")==0)
            break;

        if(forkIt() == 0){
            break;
        }

        printf("$> ");
    }

    printf("\n");
    return 1;
}

int forkIt () {
    pid_t process_id;
    int status;

    process_id = fork();
    if (process_id == -1) {
        printf("fork() failed\n");
        return -1;
    }
    if (process_id == 0) {
        execvp(tokens[0], tokens);
        perror("Error");
        return 0;
    }
    else {
        wait(NULL);
        return 1;
    }
}