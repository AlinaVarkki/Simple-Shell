/** This is the main part of our C shell program
* group 11
*/

#include <stdio.h>
#include <string.h>

int welcomeMessage();
int parsingTheLine(char*);


int main() {
    welcomeMessage();
    char *input;

    while (strcmp(input, "exit")) {
        printf("$ ");
        scanf("%s", input); //fix thsi - can't use scan f
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
    char* tokens[512];
    int i = 0;
    tokens[i] = strtok(line, " |><&;");

    while(line != NULL) {
        i++;
        tokens[i] = strtok(NULL, " |><&;");
    }
    printf("%s", tokens[0]); // also figure out this??
    return 1;
}

