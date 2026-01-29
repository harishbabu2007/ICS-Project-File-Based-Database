#ifndef TABLECREATE_H
#define TABLECREATE_H

#include<stdlib.h>
#include<stdbool.h>
#include"engine/fileops.h"

typedef enum ColDataType {
    INT,
    UNSIGNED_INT,
    STRING,
    BOOLEAN,
    FLOATING_POINT,
} col_data_type_t;


typedef struct ColItem {
    bool is_primary_key;
    unsigned char col_id;
    unsigned char len_col_name;
    col_data_type_t data_type;
    char* col_name;
} col_item_t;


typedef struct Schema {
    unsigned char len_table_name;
    unsigned char num_cols;
    int num_rows;
    int total_col_names_length;
    char *table_name;
    col_item_t* column_data;
} schema_t;


void create_new_table_schema(schema_t* table_schema);

#endif