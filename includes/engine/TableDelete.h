#ifndef TABLE_DELETE_H
#define TABLE_DELETE_H

#include "engine/engine.h"
#include "utils/utils.h"
#include "engine/TableRead.h"
#include "utils/logging.h"

int delete_row_from_table(int row, schema_t &table_schema);

#endif