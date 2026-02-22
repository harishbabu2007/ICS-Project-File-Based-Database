#include"engine/TableCreate.h"
#include"utils/utils.h"

int create_new_table_schema(schema_t table_schema) {
    // Get file stream to write;

    // TABLE HEADER

    // Max Table name size is 255
    if (!string_size_check(table_schema.table_name)) {
        logger("[ERROR] Table Name, Exceeds 255 chars\n", LOG_ERROR);
        return -1;
    }

    try {
        string schema_file_name = table_schema.table_name + "__schema_data.bin";

        FILE* schema_file = get_open_file_buffer(schema_file_name.c_str());
        
        table_schema.num_rows = 0;

        // TABLE_HEADER 13 bytes
        fwrite(&table_schema.num_rows, sizeof(table_schema.num_rows), 1, schema_file);
        fwrite(&table_schema.num_cols, sizeof(table_schema.num_cols), 1, schema_file);

        table_schema.total_row_len_inbytes = 0;
        for (int i=0; i<table_schema.num_cols; i++){
            table_schema.total_row_len_inbytes += get_size_col_data_type(
                table_schema.column_data[i]
            );
        }

        fwrite(&table_schema.total_row_len_inbytes, sizeof(table_schema.total_row_len_inbytes), 1, schema_file);

        // COL_DATA num_cols * 11 bytes
        for (int i=0; i<table_schema.num_cols; i++){
            fwrite(
                &table_schema.column_data[i].is_primary_key,
                sizeof(unsigned char), 1, schema_file
            );
            fwrite(
                &table_schema.column_data[i].data_type,
                sizeof(unsigned char), 1, schema_file
            );
            fwrite(
                &table_schema.column_data[i].is_string,
                sizeof(unsigned char), 1, schema_file
            );
            fwrite(
                &table_schema.column_data[i].max_str_len,
                sizeof(size_t), 1, schema_file
            );
        }


        // OFFSET TABLE num_cols * 8 bytes
        size_t offset = 0;
        for (int i=0; i<table_schema.num_cols; i++){
            fwrite(&offset, sizeof(offset), 1, schema_file);
            offset += get_size_col_data_type(
                table_schema.column_data[i]
            );
        }

        // STRING DATA (1+num_cols)*255 bytes
        char *buff = get_c_str_buffer_col_data(table_schema.table_name);
        fwrite(buff, sizeof(char), MAX_COL_LEN, schema_file);   
        delete[] buff; 

        for (int i=0; i<table_schema.num_cols; i++){
            string data = table_schema.column_data[i].col_name;

            if (string_size_check(data)){
                char *buff = get_c_str_buffer_col_data(data);
                fwrite(buff, sizeof(char), MAX_COL_LEN, schema_file);
                delete[] buff;
            } else {
                logger("[ERROR] Column name of ", LOG_ERROR);
                logger(data, LOG_ERROR);
                logger(" Exceeds limit of 255\n", LOG_ERROR);
                return -1;
            }
        }
        
        fclose(schema_file);

        return 0;
    } catch (const runtime_error &e) {
        return -1;
    }
}