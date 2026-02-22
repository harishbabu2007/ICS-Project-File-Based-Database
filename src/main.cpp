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
    new_schema.num_rows = 0;
    new_schema.column_data = column_data;

    int res = create_new_table_schema(new_schema);

    if (res != -1) logger("Successfully created schema\n", LOG_SUCCESS);
    else logger("Error in creating schema!\n", LOG_ERROR);

    vector<row_data_t> data_to_insert = {
       {0, make_shared<int>(0)},
       {1, make_shared<string>("b25bb1012")},
       {2, make_shared<string>("Harish Babu Balaji")},
    };

    res = append_record_to_table(new_schema, data_to_insert);

    if (res != -1) logger("Successfully Written Data\n", LOG_SUCCESS);
    else logger("Error in writing data!\n", LOG_ERROR);
}

void testing_read(){
    schema_t test_schema_of_schema = get_schema_from_schema("Students__schema_data.bin");
    cell_data_t cell_data = get_table_cell_data(0, 1, test_schema_of_schema);

    // cout << "data "  << *(int *)cell_data.cell_data.get() << endl;
    cout << "data type " << cell_data.cell_data_type << endl;
}


int main(){
    // testing_engine();
    testing_read();
    // sample_testing();
    return 0;
}