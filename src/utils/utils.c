#include "utils/utils.h"

int max_num(int a, int b) {
    return (a >= b) ? a : b;
}

size_t get_size_col_data_type(col_data_type_t data_type) {
    switch (data_type) {
        case INT:
            return sizeof(int);
        case UNSIGNED_INT:
            return sizeof(UNSIGNED_INT);
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

bool has_pk_data(schema_t* table_schema, row_data_t *pk_data, col_data_type_t pk_data_type){
    return true;
}

