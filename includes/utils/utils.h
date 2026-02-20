#ifndef UTILS_H
#define UTILS_H

#include"engine/engine.h"

size_t get_size_col_data_type(col_item_t column_data);
bool string_size_check(string data);
char* get_c_str_buffer_col_data(string data);

#endif