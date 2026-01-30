#ifndef TABLECREATE_H
#define TABLECREATE_H

#include<stdlib.h>
#include<stdbool.h>
#include"engine/engine.h"
#include"engine/fileops.h"


void create_new_table_schema(schema_t* table_schema);
size_t get_size_col_data_type(col_data_type_t data_type);


#endif