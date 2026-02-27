#include"engine/TableModify.h"
#include"engine/TableRead.h"
#include"utils/utils.h"

int cell_data_modify(schema_t schema_of_schema, cell_data_t after, int row, int col)
{
    // VARIABLES/DECLARATION

    const int th_bytes = 13;
    cell_data_t before = get_table_cell_data(row, col, schema_of_schema);

    // FILE HANDLING

    string schema_file_name = schema_of_schema.table_name + "__schema_data.bin";
    FILE *file = fopen(schema_file_name.c_str(), "rb+");

    if (!file) {
        perror("Fopen failed (schema in cell_data_modify)");
        return -1;
    }

    string table_file_name = schema_of_schema.table_name + "__table_data.bin";
    FILE *fileTable = fopen(table_file_name.c_str(), "rb+");

    if(!fileTable) {
        perror("Fopen failed (table in cell_data_modify)");
        return -2;
    }

    // HANDLING PROBABLE ERRORS

    //  1. NEW DATA TYPE IS STRING AND EXCEEDS MAX_STR_LEN

    // getting the size of the data type
    size_t col_size;  // MUST be known

    switch(before.cell_data_type){
        case STRING: {
            int max_str_len_offset_sb = th_bytes + (col*11) + 3;
            fseek(file, max_str_len_offset_sb, SEEK_SET);
            
            // reading max_str_len
            if (fread(&col_size, 1, sizeof(size_t), file) != sizeof(size_t)) return {};

            auto strPtr = static_pointer_cast<string>(after.cell_data);

            if(strPtr)
            {
                if(strPtr->length() > col_size) 
                {
                    perror("string length invalid"); //debugging
                    return -1;
                }
            }   

            break;
        }
        default:
            col_size = get_size_data_exp_string(before.cell_data_type);
    }

    // 2. DATA TYPE MISMATCH

    if (before.cell_data_type != after.cell_data_type) return -2; 

    cout << "unmodified: " << static_cast<char*>(before.cell_data.get()) << endl; // debugging

    // OVER-WRITING DATA

    // 1. reading offset for particular cell

    size_t col_offset;
    int col_offset_sb = th_bytes + (schema_of_schema.num_cols * 11) + (col * 8);
    fseek(file, col_offset_sb, SEEK_SET);
    if(fread(&col_offset, 1, sizeof(size_t), file) != sizeof(size_t)) return {};

    int cell_data_sb = (schema_of_schema.total_row_len_inbytes * row) + col_offset;

    // 2. actually over-writing

    void *info = after.cell_data.get();

    switch (after.cell_data_type)
    {
        case INT:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            fwrite(info, sizeof(int), 1, fileTable);
            break;

        case UNSIGNED_INT:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            fwrite(info, sizeof(unsigned int), 1, fileTable);
            break;

        case BOOLEAN:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            fwrite(info, sizeof(bool), 1, fileTable);
            break;

        case FLOATING_POINT:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            fwrite(info, sizeof(float), 1, fileTable);
            break;

        case DOUBLE_FLOATING_POINT:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            fwrite(info, sizeof(double), 1, fileTable);
            break;

        case UNSIGNED_CHAR:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            fwrite(info, sizeof(unsigned), 1, fileTable);
            break;

        case STRING:
            fseek(fileTable, cell_data_sb, SEEK_SET);
            string str = *(string *)info;

                    char *buffer = new char[col_size];
                    memset(buffer, 0, col_size);
                    strncpy(buffer, str.c_str(), col_size - 1);

                    fwrite(buffer, sizeof(char), col_size, fileTable);
                    delete[] buffer;
                    break;
            break;
    }

    cout << "data type: " << after.cell_data_type << endl; // debugging

    fclose(file);
    fclose(fileTable);
    return 0;
}