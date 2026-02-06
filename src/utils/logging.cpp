#include "utils/logging.h"

void logger(string buffer, log_status_t status){
    switch (status){
        case LOG_INFO:
            printf(ANSI_COLOR_RESET "%s", buffer.c_str());
            return;
        case LOG_SUCCESS:
            printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, buffer.c_str());
            return;
        case LOG_ERROR:
            printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, buffer.c_str());
            return;
        case LOG_WARNING:
            printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, buffer.c_str());
            return;
        default:
            printf(ANSI_COLOR_RESET "%s" ANSI_COLOR_RESET, buffer.c_str());
    }
}


void draw_table_line(vector<int> col_spaces){
    int num_cols = col_spaces.size();

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

    // int* col_spaces = (int *)calloc(table_data->num_cols, sizeof(int));
    vector<int> col_spaces(table_data->num_cols, 0);

    // get max spacing for each column
    for (int i=0; i<table_data->num_cols; i++){
        max_spacing = max(max_spacing, (int)(2+table_data->col_data[i].size()));
        for (int j=0; j<table_data->num_rows; j++){
            max_spacing = max(max_spacing, (int)(2+table_data->row_data[i][j].size()));
        }
        col_spaces[i] = max_spacing;
        max_spacing = -1;
    }

    // printing upper head
    draw_table_line(col_spaces);

    //printing column headings
    logger("|", LOG_SUCCESS);
    for (int i=0; i<table_data->num_cols; i++){
        int word_len = (int)table_data->col_data[i].size();
        int rem_space = col_spaces[i] - word_len;

        cout << table_data->col_data[i];
        for (int i=0; i<rem_space; i++) logger(" ", LOG_INFO);
        logger("|", LOG_SUCCESS);
    }
    cout << endl;

    // printing column end bar
    draw_table_line(col_spaces);

    // printing content of table
    for (int i=0; i<table_data->num_rows; i++){
        for (int j=0; j<table_data->num_cols; j++) {
            int word_len = (int)table_data->row_data[i][j].size();
            int rem_space = col_spaces[j] - word_len;

            logger("|", LOG_SUCCESS);
            cout << table_data->row_data[i][j];
            for (int k=0; k<rem_space; k++) logger(" ", LOG_INFO);

            if (j==table_data->num_cols-1){
                logger("|", LOG_SUCCESS);
                cout << endl;
            }
        }
        
    }

    //printing table end line
    draw_table_line(col_spaces);
}