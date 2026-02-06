#ifndef LOGGING_H
#define LOGGING_H

#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>

using namespace std;


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
    vector<vector<string>> row_data;
    vector<string> col_data;
} log_table_t;


void logger(string buffer, log_status_t status);

void log_table(log_table_t *table_data);
void draw_table_line(vector<int> col_spaces);

#endif
