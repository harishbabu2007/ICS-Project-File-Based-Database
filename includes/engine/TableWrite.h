#ifndef TABLE_WRITE_H
#define TABLE_WRITE_H

#include"engine/engine.h"
#include"utils/utils.h"

int append_record_to_table(schema_t &table_schema, vector<row_data_t> data);
int increment_num_rows(schema_t &table_schema, int increment);

#endif