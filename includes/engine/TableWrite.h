#ifndef TABLE_WRITE_H
#define TABLE_WRITE_H

#include"engine/engine.h"

int write_new_rows_table(schema_t* table_schema, row_data_t* row_data, int num_rows);

#endif