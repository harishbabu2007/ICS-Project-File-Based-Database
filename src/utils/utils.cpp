#include "utils/utils.h"

bool string_size_check(string data) {
    return data.size() <= MAX_COL_LEN;
}

char* get_c_str_buffer(string data){
    char *buffer = new char[MAX_COL_LEN]();
    strcpy(buffer, data.c_str());
    return buffer;
}

size_t get_size_col_data_type(col_item_t column_data) {
    col_data_type_t data_type = column_data.data_type;

    switch (data_type) {
        case INT:
            return sizeof(int);
        case UNSIGNED_INT:
            return sizeof(UNSIGNED_INT);
        case STRING:
            return column_data.max_str_len;
        case BOOLEAN:
            return sizeof(bool);
        case FLOATING_POINT:
            return sizeof(float);
        case DOUBLE_FLOATING_POINT:
            return sizeof(double);
        default:
            return 0;
    }
}


