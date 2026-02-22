#ifndef TABLE_READ_H
#define TABLE_READ_H

#include "engine/engine.h"

cell_data_t get_table_cell_data(int row, int col, schema_t schema_of_schema);
schema_t get_schema_from_schema(string schema_file_name);

#endif