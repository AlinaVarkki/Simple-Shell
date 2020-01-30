/** This is the main part of our C shell program
* group 11
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int welcomeMessage();
int parsingTheLine(char*);
char* trimString(char*);

int main() {
    welcomeMessage();
    char *input;

    while (strcmp(input, "exit")) {
        printf("$ ");
        fgets(input, 512, stdin);
        input = trimString(input);
        parsingTheLine(input);
        printf("%s\n", input);
    }

    return 1;
}


int welcomeMessage() {
    printf("Welcome to our Simple Shell!\n");
    return 1;
}

int parsingTheLine(char* line) {
    printf("you got here! the line that is about to be tokenised is: %s\n", line);
    char** tokens = malloc(512);
    int i = 0;
    char* token;
    tokens[i] = strtok(line, " ");

    while(line != NULL) {
        printf("do i get here?\n");

        i++;
        token = strtok(NULL, " ");
        tokens[i] = token;
    }
    printf("%s", tokens[0]); // also figure out this??
    return 1;
}

char* trimString(char* line) {
    // int index = -1;
    int i = 0;
    while (line[i] != '\0') {
        //  printf("good job, you're on the char n: %d\n",i);
        i++;
    }
    line[i-1] = '\0';
    return line;
}
