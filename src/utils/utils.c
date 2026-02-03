#include "utils/utils.h"

int max_num(int a, int b) {
    return (a >= b) ? a : b;
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


