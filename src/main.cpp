#include<stdio.h>
#include"utils/logging.h"
#include"engine/TableCreate.h"
#include"engine/TableWrite.h"
#include"interpreter/interpreter.h"
#include"engine/TableRead.h"

void sample_testing(){
    logger("Test info\n", LOG_INFO);
    logger("Test success\n", LOG_SUCCESS);
    logger("Test error\n", LOG_ERROR);
    logger("Test warning\n", LOG_WARNING);

    vector<string> columns = {"Name", "Email"};
    vector<vector<string>> rows = {
        { "John Doe", "b25xx10xx@iitj.ac.in" },
        { "Ben Dover", "b24yy101x@iitj.ac.in" },
    };

    log_table_t sample_table = {
        .num_rows = (int)rows.size(),
        .num_cols = (int)columns.size(),
        .row_data = rows,
        .col_data = columns,
    };
    
    log_table(&sample_table);
}

void testing_engine(){
    col_item_t id_col = {
        .is_primary_key = true,
        .col_id = 0,
        .data_type = UNSIGNED_INT,
        .col_name = "ID",
        .is_string = false,
        .max_str_len = 0,
    };

    col_item_t roll_col = {
        .is_primary_key = false,
        .col_id = 1, 
        .data_type = STRING,
        .col_name = "Roll No",
        .is_string = true,
        .max_str_len = 10,
    };

    col_item_t name_col = {
        .is_primary_key = false,
        .col_id = 2,
        .data_type = STRING,
        .col_name = "Name",
        .is_string = true,
        .max_str_len = 255
    };

    vector<col_item_t> column_data = {id_col, roll_col, name_col};

    schema_t new_schema;

    new_schema.table_name = "Students";
    new_schema.num_cols = (int)column_data.size();
    new_schema.column_data = column_data;

    create_new_table_schema(new_schema);
    logger("Successfully created schema\n", LOG_SUCCESS);
}

void testing_read(){
    schema_t test_schema_of_schema = get_schema_from_schema("Students__schema_data.bin");

    // printf("1 %d\n", test_schema_of_schema.num_cols);
    // printf("2 %d\n", test_schema_of_schema.num_rows);
    // printf("3 %zu\n", test_schema_of_schema.total_row_len_inbytes);
    // printf("4 %d\n", test_schema_of_schema.column_data[1].is_primary_key);
}

int main(){
    testing_engine();
    testing_read();
    // sample_testing();
    return 0;
}