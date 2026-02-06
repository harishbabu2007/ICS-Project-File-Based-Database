#include"engine/TableCreate.h"
#include"utils/utils.h"

void create_new_table_schema(schema_t* table_schema) {
    // Get file stream to write;

    // TABLE HEADER

    // Max Table name size is 255
    char *schema_file_name = strcat(table_schema->table_name, "__schema_data.bin");

    FILE* schema_file = get_open_file_buffer(schema_file_name);
    
    table_schema->num_rows = 0;

    // TABLE_HEADER 13 bytes
    fwrite(&table_schema->num_rows, sizeof(int), 1, schema_file);
    fwrite(&table_schema->num_cols, sizeof(unsigned char), 1, schema_file);

    table_schema->total_row_len_inbytes = 0;
    for (int i=0; i<table_schema->num_cols; i++){
        table_schema->total_row_len_inbytes += get_size_col_data_type(
            table_schema->column_data[i]
        );
    }

    fwrite(&table_schema->total_row_len_inbytes, sizeof(size_t), 1, schema_file);


    // COL_DATA num_cols * 7 bytes
    for (int i=0; i<table_schema->num_cols; i++){
        fwrite(
            &table_schema->column_data[i].is_primary_key,
            sizeof(unsigned char), 1, schema_file
        );
        fwrite(
            &table_schema->column_data[i].data_type,
            sizeof(unsigned char), 1, schema_file
        );
        fwrite(
            &table_schema->column_data[i].is_string,
            sizeof(unsigned char), 1, schema_file
        );
        fwrite(
            &table_schema->column_data[i].max_str_len,
            sizeof(size_t), 1, schema_file
        );
    }

    // OFFSET TABLE num_cols * 8 bytes

    size_t offset = 0;
    for (int i=0; i<table_schema->num_cols; i++){
        fwrite(&offset, sizeof(size_t), 1, schema_file);
        offset += get_size_col_data_type(
            table_schema->column_data[i]
        );
    }

    // STRING DATA (1+num_cols)*255 bytes
    fwrite(&table_schema->table_name, sizeof(char), MAX_COL_LEN, schema_file);    

    for (int i=0; i<table_schema->num_cols; i++){
        fwrite(&table_schema->column_data[i].col_name, sizeof(char), MAX_COL_LEN, schema_file);
    }
    
    fclose(schema_file);
}