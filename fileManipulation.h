//
// Created by Slavka Borovska on 20/02/2020.
//

#define SIZE_OF_HISTORY 20

int saveAliases(char* object);
char* loadAliases();
int saveHistory(char* history[], int pos);
char** loadHistory(int*);

//int saveAliases(char* object) {
//    //opening up file and setting it all up
//    char* fname = "aliases";
//    FILE *fp;
//    fp = fopen(fname, "w");
//    if (fp == NULL) {
//        return -1; }
//
//    //saving shit
//    if (object == NULL) {
//        return -1;
//    }
//    int i = 0;
//    while (object[i] != NULL)
//        fprintf(fp, "%s\n", object[i]);
//
//    //closing the file
//    int closed = fclose(fp);
//    if (closed != 0)
//        return -1;
//
//}
//
//char* loadAliases() {
//    //opens file for reading
//    char* fname = "aliases";
//    FILE *fp;
//    fp = fopen(fname, "r");
//    if (fp == NULL) {
//        return NULL; }
//
//    //reads shit
//
//    char buffer[255];
//    for(int i = 0; i < len; i++) {
//        fgets(buffer, 255, fp);
//        char* val = malloc(strlen(buffer));
//        strcpy(val, buffer);
//        val[strlen(val)-1] = '\0';
//        push(l, val);
//    }
//
//    //finishing up
//    fclose(fp);
//    return l;
//}

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
            printf("saving: %s", history[i]);
        }
        else {
            fprintf(fp, "%s\n", history[i]);
            printf("saving: %s\n", history[i]);
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
