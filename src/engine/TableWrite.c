#include"engine/TableWrite.h"
#include"utils/utils.h"

int write_new_rows_table(schema_t* table_schema, row_data_t* row_data, int num_rows){
    char table_file_name[271];
    strcpy(table_file_name, table_schema->table_name);
    strcat(table_file_name, "_table__data.bin");
    
    FILE* table_file = get_open_file_buffer(table_file_name);

    // move to end of file
    fseek(table_file, 0, SEEK_END);

    for (int i=0; i<num_rows; i++){
        row_data_t curr_row = row_data[i];

        bool is_col_string = table_schema->column_data[curr_row.col_id].is_string;

        size_t bytes_to_write = is_col_string 
        ? table_schema->column_data[curr_row.col_id].max_str_len
        : get_size_col_data_type(
            table_schema->column_data[curr_row.col_id].data_type
        );

        if (is_col_string) {
            fwrite(&curr_row.data, sizeof(char), bytes_to_write, table_file);
        } else {
            fwrite(&curr_row.data, bytes_to_write, 1, table_file);
        }        
    }

    fclose(table_file);

    return 0;
}