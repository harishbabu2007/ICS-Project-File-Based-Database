#include "engine/TableRead.h"
#include "utils/utils.h"

cell_data_t get_table_cell_data(int row, int col, schema_t schema_of_schema)
{
    string schema_file_name = schema_of_schema.table_name + "__schema_data.bin";
    FILE *file = fopen(schema_file_name.c_str(), "rb+");

    if (!file) {
        perror("Fopen failed (schema)");
        return {};
    }
    
    int th_bytes = 13;

    cell_data_t cellData;

    // READING FOR DATA TYPE

    int data_read_sb = th_bytes + (col * 11) + 1; // bytes needed to skip to get to col_data_type
    fseek(file, data_read_sb, SEEK_SET);
    if(fread(&cellData.cell_data_type, 1, 1, file) != 1) 
    { 
        perror("data_type_read failed");
        return {};
    }

    cout << cellData.cell_data_type << endl; // debugging
   
    // READING OFFSET FOR PARTICULAR CELL

    size_t col_offset;
    int col_offset_sb = th_bytes + (schema_of_schema.num_cols * 11) + (col * 8);
    fseek(file, col_offset_sb, SEEK_SET);
    if(fread(&col_offset, 1, 8, file) != 8) return {};

    // READING FOR DATA

    FILE *fileTable = fopen(schema_of_schema.table_name.c_str(), "rb+");

    if (!fileTable) {
        perror("Fopen failed (table)");
        return {};
    }

    size_t cell_data_sb = (schema_of_schema.total_row_len_inbytes * row) + col_offset;
    fseek(fileTable, cell_data_sb, SEEK_SET);
    if (fread(&cellData.cell_data, sizeof(cellData.cell_data), 1, fileTable) != 1) return {};

    fclose(file);
    fclose(fileTable);

    return cellData;
}

schema_t get_schema_from_schema(string schema_file_name)
{
    FILE *file = fopen(schema_file_name.c_str(), "rb");

    if (!file) {
        perror("Fopen failed (schema)");
        return {};
    }

    schema_t schema_of_schema;
    // TABLE HEADER BYTES
     int th_bytes = 13;

    // READING TOTAL NUM OF ROWS
    if (fread(&schema_of_schema.num_rows, sizeof(schema_of_schema.num_rows), 1, file) != 1) return {};

    // // READING TOTAL NUM OF COLS
    fseek(file, 4, SEEK_SET);
    if (fread(&schema_of_schema.num_cols, sizeof(schema_of_schema.num_cols), 1, file) != 1) return {};

    // READING TOTAL ROW LENGTH

    int row_length_sb = 5;
    fseek(file, row_length_sb, SEEK_SET);
    if (fread(&schema_of_schema.total_row_len_inbytes, 8, 1, file) != 1) return {};

    // READING TABLE NAME 

    int table_name_sb = th_bytes + (schema_of_schema.num_cols * 11) + (schema_of_schema.num_cols * 8);
    fseek(file, table_name_sb, SEEK_SET);
    char buff[MAX_COL_LEN];
    if (fread(buff, 1, MAX_COL_LEN, file) != MAX_COL_LEN) return {};
    string str(buff, MAX_COL_LEN);

    schema_of_schema.table_name = str;

    // READING COL DATA

    for (int i = 0; i < schema_of_schema.num_cols; i++)
    {
        int col_data_sb = th_bytes + (i * 11);

        col_item_t col_item;

        col_item.col_id = i; // col_id

        fseek(file, col_data_sb, SEEK_SET);
         if(fread(&col_item.is_primary_key, 1, 1, file) != 1) return {}; // is_primary_key

         if(fread(&col_item.data_type, 1, 1, file) != 1) return {}; // data_type
         if(fread(&col_item.is_string, 1, 1, file) != 1) return {}; // is_string

         if(fread(&col_item.max_str_len, 8, 1, file) != 1) return {}; // max_str_len

         int col_name_sb = th_bytes + (schema_of_schema.num_cols * 11) + (schema_of_schema.num_cols * 8) + 255;

         fseek(file, (col_name_sb + (i * 255)), SEEK_SET);
         char buff[MAX_COL_LEN];
         if (fread(buff, 1, MAX_COL_LEN, file) != MAX_COL_LEN) return {}; // col_name
         string str(buff, MAX_COL_LEN);

         col_item.col_name = str;

         schema_of_schema.column_data.push_back(col_item);
    }

    return schema_of_schema;
    fclose(file);
}