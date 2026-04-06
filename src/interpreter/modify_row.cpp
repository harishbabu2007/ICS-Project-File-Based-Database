#include "interpreter/interpreter.h"
#include "engine/TableModify.h"
#include "engine/TableRead.h"

void modify_row(vector<string> tokens) {
    int l = tokens.size();
    string tbName = tokens[1];
    string schemaName = tbName + "__schema_data.bin";
    schema_t tbSchema = get_schema_from_schema(schemaName);

    // for (size_t op = 0; op < tokens.size(); op++) {
    //     cout << op << tokens[op] << endl;
    // }

    if (tbSchema.num_cols == 0) {
        return;
    }
// appending names of columns to colNames
    vector<string> colNames;
    for (int iter = 2; iter < l-5; iter++) {
        if (tokens[iter] == "=") {
            colNames.push_back(tokens[iter-1]);
        }
    }
    // for (size_t k = 0; k < colNames.size(); k++) {
    //     cout << colNames[k] << endl;
    // }

    int numCols = tbSchema.num_cols;
    int col = -1;
    int numRows = tbSchema.num_rows;
    int whereCol = -1;
    int row = -1;
    string whereColumn = tokens[l-4];
    // cout << numCols << endl;
    // cout << numRows << endl;
    // cout << whereColumn << endl;
    for (int i = 0; i<numCols; i++) {
        if (tbSchema.column_data[i].col_name == whereColumn) {
            whereCol = i;
            break;        
        }
    }
    // cout << whereCol << endl;
    // if (col == -1 || whereCol == -1) {
    //     return;
    // }
    vector<int> mulRows; // there can be multiple rows which satisfy the where condition.
    for (int j = 0; j<numRows; j++) {
        cell_data_t cell = get_table_cell_data(j, whereCol, tbSchema);
        if (tbSchema.column_data[whereCol].data_type == STRING) {
            string res = tokens[l-2].substr(1, tokens[l-2].length()-2);
            // printf("hi");
            string cellVal = string(static_cast<char *>(cell.cell_data.get()));
            if (res == cellVal) {
                mulRows.push_back(j);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == INT) {
            if (stoi(tokens[l-2]) == *static_cast<int *>(cell.cell_data.get())) {
                mulRows.push_back(j);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == UNSIGNED_INT) {
            unsigned long temp = stoul(tokens[l-2]);
            unsigned int x = static_cast<unsigned int>(temp);
            if (x == *static_cast<unsigned int *>(cell.cell_data.get())) {
                mulRows.push_back(j);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == BOOLEAN) {
            string s = "";
            int l1 = tokens[l-2].size();
            for (int y = 0; y<l1; y++) {
                s += (char) tolower((unsigned char) tokens[l-2][y]);
            }
            bool b = (s == "true");
            if (b == *static_cast<bool *>(cell.cell_data.get())) {
                mulRows.push_back(j);
            }
        }
        else if (tbSchema.column_data[whereCol].data_type == FLOATING_POINT) {
            if (stof(tokens[l-2]) == *static_cast<float *>(cell.cell_data.get())) {
                mulRows.push_back(j);
            }    
        }
        else if (tbSchema.column_data[whereCol].data_type == DOUBLE_FLOATING_POINT) {
            if (stod(tokens[l-2]) == *static_cast<double *>(cell.cell_data.get())) {
                mulRows.push_back(j);
            } 
        }   
        else if (tbSchema.column_data[whereCol].data_type == UNSIGNED_CHAR) {
            int temp = std::stoi(tokens[l-2]);
            unsigned char c = static_cast<unsigned char>(temp);
            if (c == *static_cast<unsigned char *>(cell.cell_data.get())) {
                mulRows.push_back(j);
            }
        }
    }
    // cout << row << endl;
// modifying each column one by one
    int index = 5;
    for (size_t iter = 0; iter < colNames.size(); iter++) {
        cell_data_t after;
        string givenCol = colNames[iter]; //iterating through the names of columns
        for (int i = 0; i<numCols; i++) {
            if (tbSchema.column_data[i].col_name == givenCol) {
                col = i;
                after.cell_data_type = tbSchema.column_data[col].data_type;
                // getting the data type of each column
                // mofifying the data in each row cell by cell depending on the type
                switch (tbSchema.column_data[col].data_type)
                {
                case INT: {
                    after.cell_data = make_shared<int>(std::stoi(tokens[index])); // converting string to int
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                case UNSIGNED_INT: {
                    unsigned long temp = std::stoul(tokens[index]); // converting string to unsigned int
                    unsigned int x = static_cast<unsigned int>(temp);
                    after.cell_data = make_shared<unsigned int>(x);
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                case STRING: {
                    string res = tokens[index].substr(1, tokens[index].length()-2);
                    after.cell_data = make_shared<string>(res);
                    // cout << tokens[index] << endl;
                    // cout << tokens[index+1] << endl;
                    // cout << tokens[index+2] << endl;
                    //index += 1;
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                case BOOLEAN: {
                    bool b = (tokens[index] == "true"); // converting string to bool
                    after.cell_data = make_shared<bool>(b);
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                case FLOATING_POINT: {
                    after.cell_data = make_shared<float>(stof(tokens[index])); // converting string to float
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                case DOUBLE_FLOATING_POINT: {
                    after.cell_data = make_shared<double>(stod(tokens[index])); // converting string to double
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                case UNSIGNED_CHAR: {
                    int temp = std::stoi(tokens[index]); // converting string to unsigned char
                    unsigned char c = static_cast<unsigned char>(temp);
                    after.cell_data = make_shared<unsigned char>(c);
                    for (size_t it = 0; it < mulRows.size(); it++) {
                        row = mulRows[it];
                        cell_data_modify(tbSchema, after, row, col);
                    }
                    break;
                }
                default:
                    break;
                }
                break;        
            }
        }
        index += 4; // 
    }
}