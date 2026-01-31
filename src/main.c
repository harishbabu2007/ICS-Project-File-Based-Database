#include<stdio.h>
#include"utils/logging.h"
#include"engine/TableCreate.h"


void sample_testing(){
    logger("Test info\n", LOG_INFO);
    logger("Test success\n", LOG_SUCCESS);
    logger("Test error\n", LOG_ERROR);
    logger("Test warning\n", LOG_WARNING);

    char* columns[2] = {"Name", "Email"};
    char* rows[4] = {
        "John Doe", "b25xx10xx@iitj.ac.in",
        "Ben Dover", "b24yy101x@iitj.ac.in",
    };

    log_table_t *sample_table = new_log_table(
        2,
        2,
        columns,
        rows
    );

    log_table(sample_table);
}

void testing_engine(){
    col_item_t id_col = {
        .is_primary_key = true,
        .col_id = 0,
        .col_name = "ID",
        .data_type = UNSIGNED_INT,
    };

    col_item_t name_col = {
        .is_primary_key = false,
        .col_id = 1,
        .col_name = "name",
        .data_type = STRING,
        .is_string = true,
    };

    col_item_t roll_col = {
        .is_primary_key = false,
        .col_id = 2,
        .col_name = "Roll No",
        .data_type = STRING,
        .is_string = true,
    };

    col_item_t col_data[3] = {id_col, name_col, roll_col};

    schema_t new_schema = {
        .table_name = "Studentsa",
        .num_cols = 3,
        .column_data = col_data,
    };

    create_new_table_schema(&new_schema);
    logger("Successfully created schema\n", LOG_SUCCESS);

    // some_sample row
    // row_data_t sample_id = {.col_id = 0, .data = 0};

}

int main(){
    testing_engine();
    return 0;
}