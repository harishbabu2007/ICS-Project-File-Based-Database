#include "interpreter/interpreter.h"
#include "engine/TableModify.h"
#include "engine/TableRead.h"

void modify_row(vector<string> tokens) {
    string tbName = tokens[1];
    string schemaName = tbName + "__schema_data.bin";
    schema_t tbSchema = get_schema_from_schema(schemaName);
    string givenCol = tokens[3];
    int numCols = tbSchema.num_cols;
    int col;
    cell_data_t after;
    for (int i = 0; i<numCols; i++) {
        if (tbSchema.column_data[i].col_name == givenCol) {
            col = i;
            after.cell_data_type = tbSchema.column_data[i].data_type;
            switch (tbSchema.column_data[i].data_type)
            {
            case INT:
                after.cell_data = make_shared<int>(tokens[5]);
                break;
            case UNSIGNED_INT:
                after.cell_data = make_shared<unsigned int>(tokens[5]);
                break;
            case STRING:
                after.cell_data = make_shared<string>(tokens[5]);
                break;
            case BOOLEAN:
                after.cell_data = make_shared<bool>(tokens[5]);
                break;
            case FLOATING_POINT:
                after.cell_data = make_shared<float>(tokens[5]);
                break;
            case DOUBLE_FLOATING_POINT:
                after.cell_data = make_shared<double>(tokens[5]);
                break;
            case UNSIGNED_CHAR:
                after.cell_data = make_shared<unsigned char>(tokens[5]);
                break;
            default:
                break;
            }
            break;        
        }
    }
    int numRows = tbSchema.num_rows;
    int whereCol;
    string whereColumn = tokens[7];
    for (int i = 0; i<numCols; i++) {
        if (tbSchema.column_data[i].col_name == whereColumn) {
            whereCol = i;
            break;        
        }
    }
    for (int j = 0; j<numRows; j++) {
        switch (tbSchema.column_data[whereCol].data_type)
        {
        case INT:
            if (std::stoi(tokens[9]) == *static_cast<int *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        case UNSIGNED_INT:
            unsigned long temp = std::stoul(tokens[9]);
            unsigned int x = static_cast<unsigned int>(temp);
            if (x == *static_cast<unsigned int *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        case STRING:
            if (tokens[9] == *static_cast<string *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        case BOOLEAN:
            bool b = (tokens[9] == "true");
            if (b == *static_cast<bool *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        case FLOATING_POINT:
            if (std::stof(tokens[9]) == *static_cast<float *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        case DOUBLE_FLOATING_POINT:
            if (std::stod(tokens[9]) == *static_cast<double *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        case UNSIGNED_CHAR:
            int temp = std::stoi(tokens[9]);
            unsigned char c = static_cast<unsigned char>(temp);
            if (c == *static_cast<unsigned char *>(get_table_cell_data(j, whereCol, tbSchema).cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
                break;
            }
            break;
        default:
            break;
        }
    }
}