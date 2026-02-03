#ifndef ENGINE_H
#define ENGINE_H

#include<stdbool.h>
#include"engine/fileops.h"


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
    unsigned char len_col_name;
    col_data_type_t data_type;
    char* col_name;
    bool is_string;
    int max_str_len;
} col_item_t;


typedef struct Schema {
    unsigned char len_table_name;
    unsigned char num_cols;
    int num_rows;
    int total_col_names_length;
    size_t total_row_len_inbytes;
    char *table_name;
    col_item_t* column_data;
} schema_t;


typedef struct RowData {
    unsigned char col_id;
    void* data;
} row_data_t;


#endif