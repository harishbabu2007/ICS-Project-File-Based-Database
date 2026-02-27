#include "engine/TableDelete.h"



int delete_row_from_table(int row, schema_t table_schema) {
    // check whether we can actually proceed with deletion
    if (row >= table_schema.num_rows) return -1;

    // source file... i.e the before deletion table data
    string src_table_data_file_name = table_schema.table_name + "__table_data.bin";
    FILE* src_table_data_file = fopen(src_table_data_file_name.c_str(), "rb");
    if (!src_table_data_file) {
        perror("Error Opening table data");
        return -1;
    }
    
    // temporary file which we will rewrite everything except the deleted one
    string temp_table_data_file_name = table_schema.table_name + "_temp_table_data.bin";
    FILE* temp_table_data_file = fopen(temp_table_data_file_name.c_str(), "wb");
    if (!temp_table_data_file) {
        perror("Error Opening temp table data");
        return -1;
    }


    long record_size = table_schema.total_row_len_inbytes;
    unsigned char buffer[record_size]; // buffer to store current read

    // reading from src and writing to temp
    for (int i=0; i<table_schema.num_rows; i++){
        fseek(src_table_data_file, i*record_size, SEEK_SET); 

        if (i!=row && fread(buffer, record_size, 1, src_table_data_file) == 1){
            if (fwrite(buffer, record_size, 1, temp_table_data_file) != 1){
                perror("fwrite failed to temp file in delete");
                fclose(src_table_data_file); fclose(temp_table_data_file);
                remove(temp_table_data_file_name.c_str());
                return -1;
            }
        }
    }


    fclose(src_table_data_file);
    fclose(temp_table_data_file);

    // deleting the old file
    if (remove(src_table_data_file_name.c_str()) != 0){
        perror("Error removing old table data");
        return -1;
    }

    // renaming the temp file to become the new table data
    if (rename(temp_table_data_file_name.c_str(), src_table_data_file_name.c_str()) != 0){
        perror("Error Renaming temp file to original file");
        return -1;
    }

    return 0;
}