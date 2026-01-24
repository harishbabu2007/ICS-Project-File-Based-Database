#include "utils/logging.h"
#include "utils/utils.h"


void logger(char *buffer, log_status_t status){
    switch (status){
        case LOG_INFO:
            printf(ANSI_COLOR_RESET "%s", buffer);
            return;
        case LOG_SUCCESS:
            printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, buffer);
            return;
        case LOG_ERROR:
            printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, buffer);
            return;
        case LOG_WARNING:
            printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, buffer);
            return;
        default:
            printf(ANSI_COLOR_RESET "%s" ANSI_COLOR_RESET, buffer);
    }
}


log_table_t* new_log_table(int num_rows, int num_cols, char **col_data, char **row_data){
    log_table_t *table_data = (log_table_t *)malloc(sizeof(table_data)); 
    if (table_data == NULL) return NULL;

    table_data->num_rows = num_rows;
    table_data->num_cols = num_cols;

    table_data->col_data = col_data;
    table_data->row_data = row_data;

    return table_data;
}

void free_log_table(log_table_t* table_data) {
    free(table_data);
}

void draw_table_line(int num_cols, int col_spaces[]){
    logger("--", LOG_SUCCESS);
    for (int i=0; i<num_cols; i++){
        for (int j=0; j<col_spaces[i]; j++){
            logger("-", LOG_SUCCESS);
        }
    }
    logger("-\n", LOG_SUCCESS);
}

void log_table(log_table_t *table_data) {
    int max_spacing = -1;

    int* col_spaces = (int *)calloc(table_data->num_cols, sizeof(int));

    // get max spacing for each column
    for (int i=0; i<table_data->num_cols; i++){
        max_spacing = max_num(max_spacing, 2+strlen(table_data->col_data[i]));
        for (int j=0; j<table_data->num_rows; j++){
            max_spacing = max_num(max_spacing, 2+strlen(table_data->row_data[i + j*table_data->num_cols]));
        }
        col_spaces[i] = max_spacing;
        max_spacing = -1;
    }

    // printing upper head
    draw_table_line(table_data->num_cols, col_spaces);

    //printing column headings
    logger("|", LOG_SUCCESS);
    for (int i=0; i<table_data->num_cols; i++){
        int word_len = strlen(table_data->col_data[i]);
        int rem_space = col_spaces[i] - word_len;

        printf("%s", table_data->col_data[i]);
        for (int i=0; i<rem_space; i++) logger(" ", LOG_INFO);
        logger("|", LOG_SUCCESS);
    }
    printf("\n");

    // printing column end bar
    draw_table_line(table_data->num_cols, col_spaces);

    // printing content of table
    for (int i=0; i<table_data->num_cols*table_data->num_rows; i++){
        int current_col_index = i%table_data->num_cols;
        int word_len = strlen(table_data->row_data[i]);

        int rem_space = col_spaces[current_col_index] - word_len;

        logger("|", LOG_SUCCESS);
        printf("%s", table_data->row_data[i]);
        for (int i=0; i<rem_space; i++) logger(" ", LOG_INFO);

        if (i != 0 && i%table_data->num_cols){
            logger("|", LOG_SUCCESS);
            logger("\n", LOG_INFO);
        }
    }

    //printing table end line
    draw_table_line(table_data->num_cols, col_spaces);

    // some garbage collection
    free_log_table(table_data);
    free(col_spaces);
}