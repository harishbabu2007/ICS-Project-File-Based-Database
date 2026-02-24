#include "engine/TableRead.h"
#include "utils/utils.h"

cell_data_t get_table_cell_data(int row, int col, schema_t schema_of_schema)
{
    string schema_file_name = schema_of_schema.table_name + "__schema_data.bin";
    FILE *file = fopen(schema_file_name.c_str(), "rb+");

    if (file == nullptr) {
        perror("Fopen failed (get_table_cell_data)");
        return {};
    }
    
    int th_bytes = 13;

    cell_data_t cellData{};

    // READING FOR DATA TYPE

    int data_read_sb = th_bytes + (col * 11) + 1; // bytes needed to skip to get to col_data_type
    fseek(file, data_read_sb, SEEK_SET);
    if(fread(&cellData.cell_data_type, 1, 1, file) != 1) 
    { 
        perror("data_type_read failed");
        return {};
    }

    // READING FOR DATA

    string table_file_name = schema_of_schema.table_name + "__table_data.bin";
    FILE *fileTable = fopen(table_file_name.c_str(), "rb+");

    if (!fileTable) {
        perror("Fopen failed (table in get_cell_data)");
        return {};
    }


    // getting the size of the data type
    size_t col_size;  // MUST be known

    switch(cellData.cell_data_type){
        case STRING: {
            int max_str_len_offset_sb = th_bytes + (col*11) + 3;
            fseek(file, max_str_len_offset_sb, SEEK_SET);
            
            // reading max_str_len
            if (fread(&col_size, 1, sizeof(size_t), file) != sizeof(size_t)) return {};

            break;
        }
        default:
            col_size = get_size_data_exp_string(cellData.cell_data_type);
    }

    // READING OFFSET FOR PARTICULAR CELL
    size_t col_offset;
    int col_offset_sb = th_bytes + (schema_of_schema.num_cols * 11) + (col * 8);
    fseek(file, col_offset_sb, SEEK_SET);
    if(fread(&col_offset, 1, sizeof(size_t), file) != sizeof(size_t)) return {};

    // Actually reading the data
    auto buffer = std::shared_ptr<char[]>(
    new char[col_size],
        std::default_delete<char[]>()
    );

    size_t cell_data_sb = (schema_of_schema.total_row_len_inbytes * row) + col_offset;
    fseek(fileTable, cell_data_sb, SEEK_SET);
    if (fread(buffer.get(), col_size, 1, fileTable) != 1) return {};

    cellData.cell_data = buffer;

    fclose(file);
    fclose(fileTable);

    return cellData;
}

schema_t get_schema_from_schema(string schema_file_name)
{
    FILE *file = fopen(schema_file_name.c_str(), "rb");

    if (!file) {
        perror("Fopen failed (get_schema_from_schema)");
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
    string str(buff);

    schema_of_schema.table_name = str;

    // READING COL DATA

    for (int i = 0; i < schema_of_schema.num_cols; i++)
    {
        int col_data_sb = th_bytes + (i * 11);

        col_item_t col_item;

        col_item.col_id = i; // col_id

        fseek(file, col_data_sb, SEEK_SET);
         if(fread(&col_item.is_primary_key, sizeof(col_item.is_primary_key), 1, file) != 1) return {}; // is_primary_key

         if(fread(&col_item.data_type, sizeof(col_item.data_type), 1, file) != 1) return {}; // data_type
         if(fread(&col_item.is_string, sizeof(col_item.is_string), 1, file) != 1) return {}; // is_string

         if(fread(&col_item.max_str_len, sizeof(col_item.max_str_len), 1, file) != 1) return {}; // max_str_len

         int col_name_sb = th_bytes + (schema_of_schema.num_cols * 11) + (schema_of_schema.num_cols * 8) + 255;

         fseek(file, (col_name_sb + (i * MAX_COL_LEN)), SEEK_SET);
         char buff[MAX_COL_LEN];
         if (fread(buff, 1, MAX_COL_LEN, file) != MAX_COL_LEN) return {}; // col_name
         string str(buff, MAX_COL_LEN);

         col_item.col_name = str;

         schema_of_schema.column_data.push_back(col_item);
    }

    fclose(file);
    return schema_of_schema;
}