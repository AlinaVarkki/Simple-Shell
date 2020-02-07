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

int forkIt(char** tokens);

int main() {
    welcomeMessage();
    char input[512];

    while (strcmp(input, "exit")) {
        printf("$> ");
        char* checkInput = fgets(input, 512, stdin);
        // Picking up empty command

        if (checkInput == NULL) {
            printf("\n");
            exit(1);
        }

        if(strlen(checkInput) == 1){
            continue;
        }


        trimString(input);
        char** tokens;
        tokens = parsingTheLine(input);
        if(forkIt(tokens) == 0){
            break;
        }
    }

    return 1;
}

int forkIt (char** tokens) {
    pid_t process_id;
    int status;

    process_id = fork();
    if (process_id == -1) {
        printf("fork() failed\n");
        return -1;
    }
    if (process_id == 0) {
        execvp("", tokens);
        perror(tokens[0]);
        printf("Here 1\n");
        return 0;
    }
    else {
        printf ("Here 2\n");
        wait(NULL);
        return 1;
    }
}