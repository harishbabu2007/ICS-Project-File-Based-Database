#ifndef ENGINE_H
#define ENGINE_H

#include"engine/fileops.h"
#include<bits/stdc++.h>

using namespace std;

#define MAX_COL_LEN 255


typedef enum ColDataType {
    INT,
    UNSIGNED_INT,
    STRING,
    BOOLEAN,
    FLOATING_POINT,
    DOUBLE_FLOATING_POINT,
    UNSIGNED_CHAR,
} col_data_type_t;


typedef struct ColItem {
    bool is_primary_key;
    unsigned char col_id;
    col_data_type_t data_type;
    string col_name;
    bool is_string;
    size_t max_str_len;
} col_item_t;


typedef struct Schema {
    string table_name;
    unsigned char num_cols;
    int num_rows;
    size_t total_row_len_inbytes;
    vector<col_item_t> column_data;
} schema_t;


typedef struct RowData {
    unsigned char col_id;
    void* data;
} row_data_t;


#endif