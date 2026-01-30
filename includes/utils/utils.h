#ifndef UTILS_H
#define UTILS_H

#include"engine/engine.h"

int max_num(int a, int b);
size_t get_size_col_data_type(col_data_type_t data_type);
bool has_pk_data(schema_t* table_schema, row_data_t *pk_data, col_data_type_t pk_data_type);

#endif