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
//    fgets(input, 512, stdin);
    printf("$> ");

    while (    fgets(input, 512, stdin)!=NULL){
//    while (strcmp(input, "exit")) {
        if(strlen(input) == 1){
            printf("$> ");
            continue;
        }


        tokens = parsingTheLine(input);

        if(strcmp(tokens[0],"exit")==0)
            break;
//        if (input == NULL) {
//            printf("\n");
//            exit(1);
//        }



//        trimString(input);

//        tokens = parsingTheLine(input);
        if(forkIt() == 0){
            break;
        }
        printf("$> ");

        // Picking up empty command
    }

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
        printf("%s\n",tokens[0]);
        execvp(tokens[0], tokens);
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