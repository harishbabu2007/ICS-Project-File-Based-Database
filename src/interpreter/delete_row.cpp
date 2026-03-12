#include "interpreter/interpreter.h"
#include "engine/TableRead.h"
#include "engine/TableDelete.h"

void delete_row(string table_name,int n){
    string tab = table_name;
    schema_t schema = get_schema_from_schema(tab+"__schema_data.bin");

    if (schema.num_cols == 0) {
        logger("Cannot delete row: schema load failed or table does not exist\n", LOG_ERROR);
        return;
    }

    int row_to_delete = n;
    int result = delete_row_from_table(row_to_delete, schema);

    if (result == 0) {
        // Row deleted successfully; schema file is updated by delete function
        cout << "Rows remaining: " << schema.num_rows << endl;
    } else {
        logger("Error deleting row (row may not exist)\n", LOG_ERROR);
    }
}