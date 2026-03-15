#include "interpreter/interpreter.h"
#include "engine/TableModify.h"
#include "engine/TableRead.h"

void modify_row(vector<string> tokens) {
    string tbName = tokens[1];
    string schemaName = tbName + "__schema_data.bin";
    schema_t tbSchema = get_schema_from_schema(schemaName);
    if (tbSchema.num_cols == 0) {
        return;
    }
    string givenCol = tokens[3];
    int numCols = tbSchema.num_cols;
    int col = -1;
    cell_data_t after;
    for (int i = 0; i<numCols; i++) {
        if (tbSchema.column_data[i].col_name == givenCol) {
            col = i;
            after.cell_data_type = tbSchema.column_data[i].data_type;
            switch (tbSchema.column_data[i].data_type)
            {
            case INT: {
                after.cell_data = make_shared<int>(std::stoi(tokens[5]));
                break;
            }
            case UNSIGNED_INT: {
                unsigned long temp = std::stoul(tokens[5]);
                unsigned int x = static_cast<unsigned int>(temp);
                after.cell_data = make_shared<unsigned int>(x);
                break;
            }
            case STRING: {
                after.cell_data = make_shared<string>(tokens[5]);
                break;
            }
            case BOOLEAN: {
                string s = "";
                int l = tokens[5].size();
                for (int y = 0; y<l; y++) {
                    s += (char) tolower((unsigned char) tokens[5][y]);
                }
                bool b = (s == "true" || s == "1");
                after.cell_data = make_shared<bool>(b);
                break;
            }
            case FLOATING_POINT: {
                after.cell_data = make_shared<float>(stof(tokens[5]));
                break;
            }
            case DOUBLE_FLOATING_POINT: {
                after.cell_data = make_shared<double>(stod(tokens[5]));
                break;
            }
            case UNSIGNED_CHAR: {
                int temp = std::stoi(tokens[5]);
                unsigned char c = static_cast<unsigned char>(temp);
                after.cell_data = make_shared<unsigned char>(c);
                break;
            }
            default:
                break;
            }
            break;        
        }
    }
    int numRows = tbSchema.num_rows;
    int whereCol = -1;
    string whereColumn = tokens[7];
    for (int i = 0; i<numCols; i++) {
        if (tbSchema.column_data[i].col_name == whereColumn) {
            whereCol = i;
            break;        
        }
    }
    if (col == -1 || whereCol == -1) {
        return;
    }
    for (int j = 0; j<numRows; j++) {
        cell_data_t cell = get_table_cell_data(j, whereCol, tbSchema);
        if (tbSchema.column_data[whereCol].data_type == STRING) {
            string cellVal = string(static_cast<char *>(cell.cell_data.get()));
            if (tokens[9] == cellVal) {
                cell_data_modify(tbSchema, after, j, col);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == INT) {
            if (std::stoi(tokens[9]) == *static_cast<int *>(cell.cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == UNSIGNED_INT) {
            unsigned long temp = std::stoul(tokens[9]);
            unsigned int x = static_cast<unsigned int>(temp);
            if (x == *static_cast<unsigned int *>(cell.cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == BOOLEAN) {
            string s = "";
            int l = tokens[9].size();
            for (int y = 0; y<l; y++) {
                s += (char) tolower((unsigned char) tokens[9][y]);
            }
            bool b = (s == "true" || s == "1");
            if (b == *static_cast<bool *>(cell.cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == FLOATING_POINT) {
            if (std::stof(tokens[9]) == *static_cast<float *>(cell.cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
            }    
        }
        else if (tbSchema.column_data[whereCol].data_type == DOUBLE_FLOATING_POINT) {
            if (std::stod(tokens[9]) == *static_cast<double *>(cell.cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
            } 
        }   
        else if (tbSchema.column_data[whereCol].data_type == UNSIGNED_CHAR) {
            int temp = std::stoi(tokens[9]);
            unsigned char c = static_cast<unsigned char>(temp);
            if (c == *static_cast<unsigned char *>(cell.cell_data.get())) {
                cell_data_modify(tbSchema, after, j, col);
            }   
        }
    }
}