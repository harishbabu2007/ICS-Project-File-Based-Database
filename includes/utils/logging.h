#ifndef LOGGING_H
#define LOGGING_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
// #define ANSI_COLOR_BLUE    "\x1b[34m"
// #define ANSI_COLOR_MAGENTA "\x1b[35m"
// #define ANSI_COLOR_CYAN    "\x1b[36m"


typedef enum LogStatus {
    LOG_INFO,
    LOG_SUCCESS,
    LOG_ERROR,
    LOG_WARNING,
} log_status_t;

typedef struct LogTable {
    int num_rows;
    int num_cols;
    char **row_data;
    char **col_data;
} log_table_t;


void logger(char *buffer, log_status_t status);

log_table_t* new_log_table(int num_rows, int num_cols, char **row_data, char **col_heads);
void free_log_table(log_table_t* table_data);
void log_table(log_table_t *table_data);

#endif
