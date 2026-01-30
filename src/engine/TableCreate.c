#include"engine/TableCreate.h"
#include"utils/utils.h"

void create_new_table_schema(schema_t* table_schema) {
    // Get file stream to write;

    // TABLE HEADER

    // Max Table name size is 255
    char schema_file_name[272];
    strcpy(schema_file_name, table_schema->table_name);
    strcat(schema_file_name, "_schema__data.bin");

    table_schema->len_table_name = strlen(table_schema->table_name);
    table_schema->num_rows = 0;
    table_schema->total_col_names_length = 0;

    FILE* schema_file = get_open_file_buffer(schema_file_name);
    
    fwrite(&table_schema->num_rows, sizeof(int), 1, schema_file);
    fwrite(&table_schema->num_cols, sizeof(unsigned char), 1, schema_file);
    // fwrite(&table_schema->len_table_name, sizeof(unsigned char), 1, schema_file);

    for (int i=0; i<table_schema->num_cols; i++){
        int len_name = strlen(
            table_schema->column_data[i].col_name
        );

        table_schema->total_col_names_length += len_name;
        table_schema->column_data[i].len_col_name = len_name;
    }

    fwrite(&table_schema->total_col_names_length, sizeof(int), 1, schema_file);

    // COLUMN DATA

    for (int i=0; i<table_schema->num_cols; i++){
        fwrite(&table_schema->column_data[i].is_primary_key, sizeof(bool), 1, schema_file);
        fwrite(&table_schema->column_data[i].data_type, sizeof(unsigned char), 1, schema_file);
        fwrite(&table_schema->column_data[i].len_col_name, sizeof(unsigned char), 1, schema_file);
    }


    // OFFSET TABLE

    int _data_offset = 0;
    for (int i=0; i<table_schema->num_cols; i++){
        fwrite(&table_schema->column_data[i].col_id, sizeof(unsigned char), 1, schema_file);
        fwrite(&_data_offset, sizeof(unsigned char), 1, schema_file);

        _data_offset += (table_schema->column_data[i].is_string) ? table_schema->column_data[i].max_str_len
         : (int)get_size_col_data_type(table_schema->column_data[i].data_type);
    }


    // NAMES TABLE
    
    // write 1+len_table_name bytes, for table name
    fwrite(&table_schema->len_table_name, sizeof(unsigned char), 1, schema_file);
    fwrite(&table_schema->table_name, sizeof(char), table_schema->len_table_name, schema_file);

    for (int i=0; i<table_schema->num_cols; i++){
        fwrite(&table_schema->column_data[i].col_id, sizeof(unsigned char), 1, schema_file);
        fwrite(&table_schema->column_data[i].col_name, sizeof(char), table_schema->column_data[i].len_col_name, schema_file);
    }


    // CLOSE FILE buffer
    fclose(schema_file);
}