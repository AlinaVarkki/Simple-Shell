//
// Created by Slavka Borovska on 20/02/2020.
//

#define SIZE_OF_HISTORY 20

int saveAliases();
int loadAliases();
int saveHistory(char* history[], int pos);
char** loadHistory(int*);

int saveAliases() {
    //opening up file and setting it all up
    char* fname = ".aliases";
    FILE *fp;
    fp = fopen(fname, "w");
    if (fp == NULL) {
        return -1; }

    //saving
    if (alias_counter == 0) {
        return 0;
    }

    for(int i = 0; i < alias_counter; i++) {
        fprintf(fp, "alias %s %s\n", aliases[i].name, aliases[i].command);
    }

    //closing the file
    int closed = fclose(fp);
    if (closed != 0) {
        return -1;
    }
    return 1;

}

int loadAliases() {
    //opens file for reading
    char* fname = ".aliases";
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return 0; }

    //reads shit
    char** temp;
    char buffer[512];
    while(fgets(buffer, 512, fp) != NULL) {
        temp = parsingTheLine(buffer);
        if(strcmp(temp[0],"alias") == 0 && temp[1] != NULL && temp[2] != NULL){
            aliasThis(temp);
        }
        else{
            printf("Malformed alias, skipping\n");
        }
    }


    //finishing up
    int closed = fclose(fp);
    if (closed != 0)
        return closed;
    return alias_counter;
}

int saveHistory(char* history[SIZE_OF_HISTORY], int pos) {
    //opening up file and setting it all up
    char* fname = ".hist_list";
    FILE *fp;
    fp = fopen(fname, "w");
    if (fp == NULL) {
        return -1; }

    //saving

    //check if there is something in history to save
    if (history == NULL) {
        return -1;
    }

    //saving history
    fprintf(fp, "%d\n", pos);
    int i = 0;
    while (i<SIZE_OF_HISTORY && i<pos) {
        if (history[i][strlen(history[i])-1]=='\n') {
            fprintf(fp, "%s", history[i]);
        }
        else {
            fprintf(fp, "%s\n", history[i]);
        }
        i++;
    }
    //closing the file
    int closed = fclose(fp);
    if (closed != 0)
        return -1;
    return 1;
}

char** loadHistory(int* commandNum) {
    char** tempHistory1 = malloc(512);
    //opens file for reading
    char* fname = ".hist_list";
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return NULL; }

    //reads shit
    char buffer[512];
    int pos = 0;
    fscanf(fp, "%d\n", &pos);
    int i = 0;
    while (i<SIZE_OF_HISTORY && i<pos) {
        fgets(buffer, 512, fp);
        char* tempCommand = malloc(512);
        strcpy(tempCommand, buffer);
        tempHistory1[i] = tempCommand;
        //printf("%d. command loading: %s",i+1, tempHistory1[i]);
        i++;
    }
    //finishing up
    *commandNum = pos;
    fclose(fp);
    return tempHistory1;
}
