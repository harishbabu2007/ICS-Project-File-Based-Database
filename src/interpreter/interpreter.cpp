#include "interpreter/interpreter.h"


int index_fromtable(char **a, int count) {
    int indf = -1;
    for (int k = 0; k < count-1; k++) {
        if (strcmp(a[k], "from") == 0 && strcmp(a[k+1], "table") == 0) {
            indf = k;
        }

    }
    return indf;
}

int index_selectdata(char **a, int count) {
    int inds = -1;
    for (int k = 0; k < count-1; k++) {
        if (strcmp(a[k], "select") == 0 && strcmp(a[k+1], "data") == 0) {
            inds = k;
        }

    }
    return inds;
}

int index_createtable(char **a, int count) {
    int indc = -1;
    for (int k = 0; k < count-1; k++) {
        if (strcmp(a[k], "create") == 0 && strcmp(a[k+1], "table") == 0) {
            indc = k;
        }

    }
    return indc;
}

int index_insertinto(char **a, int count) {
    int indi = -1;
    for (int k = 0; k < count-1; k++) {
        if (strcmp(a[k], "insert") == 0 && strcmp(a[k+1], "into") == 0) {
            indi = k;
        }

    }
    return indi;
}

void interpreter_testing() {
    printf("Interpreter Running... \n");
    while (true) {
        printf(">>> ");

        char *query;
        int ch;
        size_t size = init_max_query_length; // Initial capacity
        size_t len = 0;

        query = (char *)malloc(sizeof(*query) * size); // Allocating initial memory

        while ((ch = getchar()) != '\n') { // Reading characters until enter key is pressed
            ch = tolower((unsigned char)ch);
            query[len] = ch;
            len++;

            if (len == size-1) { // doubling capacity when we are about to run out of space
                size += 100;
                char *temp = (char *)realloc(query, sizeof(*query) * size);
                query = temp;
        }
        }
        query[len] = '\0'; // Null termination

        char **tokens = (char **)malloc(len * sizeof(char *)); // tokenization starts here
        int count = 0;
        char *tok = strtok(query, " "); // first token

        while (tok != NULL) {
            tokens[count] = tok; // sending each word of query into query
            count++;
            tok = strtok(NULL, " "); // tok takes the next word of query into it. NULL prevents it from going to the first word
        }

        for (int j = 0; j < count; j++) {
            printf("%d %s\n", j, tokens[j]); // printing to check if it works for now
        }
        
        int index_select = index_selectdata(tokens, count); // printing to check if it works
        int index_from = index_fromtable(tokens, count);
        int index_create = index_createtable(tokens, count);
        int index_insert = index_insertinto(tokens, count);
        printf("%d %d %d %d\n", index_select, index_from, index_create, index_insert);    

        free(tokens);
        free(query);
    }
}