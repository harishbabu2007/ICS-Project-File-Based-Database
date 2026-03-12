#include "engine/TableDelete.h"
#include "engine/TableWrite.h"     
#include "utils/logging.h"
#include <vector>

int delete_row_from_table(int row, schema_t &table_schema) {
    // ensure valid row index
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
    std::vector<unsigned char> buffer(record_size);

    // reading from src and writing to temp
    for (int i = 0; i < table_schema.num_rows; i++) {
        fseek(src_table_data_file, i * record_size, SEEK_SET);

        if (i != row && fread(buffer.data(), record_size, 1, src_table_data_file) == 1) {
            if (fwrite(buffer.data(), record_size, 1, temp_table_data_file) != 1) {
                perror("fwrite failed to temp file in delete");
                fclose(src_table_data_file);
                fclose(temp_table_data_file);
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
    if (rename(temp_table_data_file_name.c_str(), src_table_data_file_name.c_str()) != 0) {
        perror("Error Renaming temp file to original file");
        return -1;
    }

    // decrement count on-disk and in-memory through helper
    // `increment_num_rows` already adjusts the passed schema object, so we
    // should not subtract manually here or else the count will drop twice.
    if (increment_num_rows(table_schema, -1) != 0) {
        logger("Warning: failed to update schema num_rows on disk\n", LOG_WARNING);
    }

    return 0;
}