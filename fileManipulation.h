//
// Created by Slavka Borovska on 20/02/2020.
//

#ifndef UNTITLED_FILEMANIPULATION_H
#define UNTITLED_FILEMANIPULATION_H

#endif //UNTITLED_FILEMANIPULATION_H
#define SIZE_OF_HISTORY 20

int saveAliases(char* object);
char* loadAliases();
int saveHistory(char* history[], int pos);
char* loadHistory(int*, char* history[SIZE_OF_HISTORY]);

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

    //saving shit

    //check if there is something in history to save
    if (history == NULL) {
        return -1;
    }

    //saving history
    fprintf(fp, "%d\n", pos);
    int i = 0;
    while (i<20 && i<pos) {
        if (history[i][strlen(history[i])-1]=='\n')
            fprintf(fp, "%s", history[i]);
        fprintf(fp, "%s\n", history[i]);
        i++;
    }
    //closing the file
    int closed = fclose(fp);
    if (closed != 0)
        return -1;
    return 1;
}

char* loadHistory(int* commandNum, char* history[SIZE_OF_HISTORY]) {
    //opens file for reading

    char* fname = ".hist_list";
    FILE *fp;
    fp = fopen(fname, "r");

    if (fp == NULL) {
        return NULL; }

    //reads shit
    char buffer[255];
    int pos = 0;
    fscanf(fp, "%d\n", &pos);
    printf("%d\n", pos);
    int i = 0;
    while (i<SIZE_OF_HISTORY && i<pos) {
        char* val;
        fgets(buffer, 512, fp);
        printf("%s\n",buffer);
        i++;
        }

//        char* val = malloc(strlen(buffer));
//        strcpy(val, buffer);
//        if(val == NULL) {
//            printf("here\n");
//            continue; }
//        val[strlen(val)-1] = '\n';
//        int x = (pos+i)%SIZE_OF_HISTORY;
//        printf("%d: %s\n", x, val);
//        history[i] = val;

    *commandNum = pos%20;
    //finishing up
    fclose(fp);
    return *history;
}