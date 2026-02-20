#include"engine/TableWrite.h"



int append_record_to_table(schema_t table_schema, vector<row_data_t> data) {
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

            switch(data_type){
                case INT:
                    fwrite(info, sizeof(int), 1, table_file);
                    break;
                case UNSIGNED_INT:
                    fwrite(info, sizeof(unsigned int), 1, table_file);
                    break;
                case STRING: {
                    string str = *(string *)info;
                    
                    int max_size = table_schema.column_data[i].max_str_len;
                    char *buffer = new char[max_size];
                    strncpy(buffer, str.c_str(), max_size - 1);

                    fwrite(buffer, sizeof(char), max_size, table_file);
                    delete[] buffer;
                    break;
                }
                case BOOLEAN:
                    fwrite(info, sizeof(bool), 1, table_file);
                    break;
                case FLOATING_POINT:
                    fwrite(info, sizeof(float), 1, table_file);
                    break;
                case DOUBLE_FLOATING_POINT:
                    fwrite(info, sizeof(double), 1, table_file);
                    break;
                case UNSIGNED_CHAR:
                    fwrite(info, sizeof(unsigned char), 1, table_file);
                    break;
                default:
                    break;
            }
        }

        fclose(table_file);
        return 0;
    } catch (runtime_error &e){
        fclose(table_file);
        return -1;
    }
}