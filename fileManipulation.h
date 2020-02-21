//
// Created by Slavka Borovska on 20/02/2020.
//

#ifndef UNTITLED_FILEMANIPULATION_H
#define UNTITLED_FILEMANIPULATION_H

#endif //UNTITLED_FILEMANIPULATION_H

int saveAliases(char* object);
char* loadAliases(;
int saveHistory(char* object, int pos);
char* loadHistory();

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

int saveHistory(char* object, int pos) {
    //opening up file and setting it all up
    char* fname = ".hist_list";
    FILE *fp;
    fp = fopen(fname, "w");
    if (fp == NULL) {
        return -1; }

    //saving shit

    //check if there is something in history to save
    if (object == NULL) {
        return -1;
    }

    //saving history
    fprintf(fp, "%d\n", pos);
    int i = 0;
    while (i<20 && i<pos) {
        fprintf(fp, "%s\n", object[i]);
        i++;
    }
    //closing the file
    int closed = fclose(fp);
    if (closed != 0)
        return -1;

}

char* loadHistory() {
    char* history[20];
    //opens file for reading
    char* fname = ".hist_list";
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return NULL; }

    //reads shit
    char buffer[255];
    int pos;
    fscanf(fp, "%d\n",  &pos);
    int i = 0;
    while (i<20 && i<pos) {
        fgets(buffer, 255, fp);
        char* val = malloc(strlen(buffer));
        strcpy(val, buffer);
        val[strlen(val)-1] = '\0';
        history[(pos+i)%20] = val;
    }
    //finishing up
    fclose(fp);
    return history;
}