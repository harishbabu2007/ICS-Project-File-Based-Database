#include"engine/TableWrite.h"

int increment_num_rows(schema_t &table_schema, int increment){
    string schema_file_name = table_schema.table_name + "__schema_data.bin";
    
    FILE* schema_file = fopen(
        schema_file_name.c_str(),
        "r+b"
    );

    if (!schema_file) return -1;

    fseek(schema_file, 0, SEEK_SET);

    table_schema.num_rows += increment;
    fwrite(&table_schema.num_rows, sizeof(table_schema.num_rows), 1, schema_file);
    fclose(schema_file);

    return 0;
}


int append_record_to_table(schema_t &table_schema, vector<row_data_t> data) {
    string table_file_name = table_schema.table_name + "__table_data.bin";

    FILE* table_file = fopen(table_file_name.c_str(), "ab+");
    if (table_file == NULL) return -1;

    try {
        // go to end of file
        fseek(table_file, 0L, SEEK_END);

        for (int i=0; i<table_schema.num_cols; i++){
            int col_id = data[i].col_id;
            col_data_type_t data_type = table_schema.column_data[col_id].data_type;
            void* info = data[i].data.get();

            // If the value pointer is null, treat as NULL: write zero bytes of
            // the appropriate width (string gets all zeros). This mirrors how
            // a column with no data should behave.
            bool isNull = (info == nullptr);

            switch(data_type){
                case INT: {
                    int zero = 0;
                    fwrite(isNull ? &zero : info, sizeof(int), 1, table_file);
                    break;
                }
                case UNSIGNED_INT: {
                    unsigned int zero = 0;
                    fwrite(isNull ? &zero : info, sizeof(unsigned int), 1, table_file);
                    break;
                }
                case STRING: {
                    int max_size = table_schema.column_data[i].max_str_len;
                    char *buffer = new char[max_size];
                    memset(buffer, 0, max_size);
                    if (!isNull) {
                        string str = *(string *)info;
                        strncpy(buffer, str.c_str(), max_size - 1);
                    }
                    fwrite(buffer, sizeof(char), max_size, table_file);
                    delete[] buffer;
                    break;
                }
                case BOOLEAN: {
                    bool zero = false;
                    fwrite(isNull ? &zero : info, sizeof(bool), 1, table_file);
                    break;
                }
                case FLOATING_POINT: {
                    float zero = 0.0f;
                    fwrite(isNull ? &zero : info, sizeof(float), 1, table_file);
                    break;
                }
                case DOUBLE_FLOATING_POINT: {
                    double zero = 0.0;
                    fwrite(isNull ? &zero : info, sizeof(double), 1, table_file);
                    break;
                }
                case UNSIGNED_CHAR: {
                    unsigned char zero = 0;
                    fwrite(isNull ? &zero : info, sizeof(unsigned char), 1, table_file);
                    break;
                }
                // case NULL_TYPE:
                //     // column has zero width; nothing to write
                //     break;
                default:
                    break;
            }
        }

        fclose(table_file);
    } catch (runtime_error &e){
        fclose(table_file);
        return -1;
    }


    // update num rows in schema and return that status code
    return increment_num_rows(table_schema, 1);
}

