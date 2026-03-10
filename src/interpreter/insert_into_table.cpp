#include "interpreter/interpreter.h"
#include "engine/TableWrite.h"
#include "engine/TableRead.h"

// void insert_into_table(vector<string> tokens)
// {
//     string table_name = tokens[2];

//     schema_t table_schema =
//     get_schema_from_schema(table_name + "__schema_data.bin");

//     size_t num_cols = table_schema.num_cols;

//     // Find VALUES
//     int values_index = -1;
//     for (size_t i = 0; i < tokens.size(); i++)
//     {
//         if (tokens[i] == "VALUES")
//         {
//             values_index = i;
//             break;
//         }
//     }
//     vector<vector<row_data_t>> all_rows;
//     vector<string> current_row_values;

//     for (size_t i = values_index + 1; i < tokens.size(); i++)
//     {
//         if (tokens[i] == "(")
//         {
//             current_row_values.clear();
//         }
//         else if (tokens[i] == ")")
//         {
//             if (current_row_values.size() != num_cols)
//             {
//                 logger("Column count mismatch\n", LOG_ERROR);
//                 return;
//             }

//             vector<row_data_t> row_data;

//             for (size_t col = 0; col < num_cols; col++)
//             {
//                 row_data_t cell;
//                 cell.col_id = col;

//                 col_data_type_t type =
//                     table_schema.column_data[col].data_type;

//                 string value = current_row_values[col];

//                 try
//                 {
//                     switch (type)
//                     {
//                         case INT:
//                         {
//                             int v = stoi(value);
//                             cell.data = make_shared<int>(v);
//                             break;
//                         }

//                         case UNSIGNED_INT:
//                         {
//                             unsigned int v = stoul(value);
//                             cell.data = make_shared<unsigned int>(v);
//                             break;
//                         }

//                         case STRING:
//                         {
//                             cell.data = make_shared<string>(value);
//                             break;
//                         }

//                         case BOOLEAN:
//                         {
//                             bool v = (value == "true" || value == "1");
//                             cell.data = make_shared<bool>(v);
//                             break;
//                         }

//                         case FLOATING_POINT:
//                         {
//                             float v = stof(value);
//                             cell.data = make_shared<float>(v);
//                             break;
//                         }

//                         case DOUBLE_FLOATING_POINT:
//                         {
//                             double v = stod(value);
//                             cell.data = make_shared<double>(v);
//                             break;
//                         }

//                         case UNSIGNED_CHAR:
//                         {
//                             unsigned char v =
//                                 static_cast<unsigned char>(stoi(value));
//                             cell.data = make_shared<unsigned char>(v);
//                             break;
//                         }

//                         case NULL_TYPE:
//                         {
//                             cell.data = nullptr;
//                             break;
//                         }

//                         default:
//                             logger("Unknown data type\n", LOG_ERROR);
//                             return;
//                     }
//                 }
//                 catch (...)
//                 {
//                     logger("Type conversion error\n", LOG_ERROR);
//                     return;
//                 }

//                 row_data.push_back(cell);
//             }

//             all_rows.push_back(row_data);
//         }
//         else if (tokens[i] == "," || tokens[i] == ";")
//         {
//             continue;
//         }
//         else
//         {
//             current_row_values.push_back(tokens[i]);
//         }
//     }

//     // Write all rows
//     for (auto &row : all_rows)
//     {
//         int result = append_record_to_table(table_schema, row);

//         if (result == 0)
//             logger("Successfully Written Data\n", LOG_SUCCESS);
//         else
//             logger("Error in writing data!\n", LOG_ERROR);
//     }
// }
// #include "interpreter/interpreter.h"
// #include "engine/TableRead.h"
// #include "engine/TableWrite.h"

// void append_row(vector<string> tokens) {
//     string table_Name = tokens[2];
//     table_Name += "__schema_data.bin";
//     schema_t table_Schema_for_Append = get_schema_from_schema(table_Name);
//     vector<row_data_t> data;
//     int num_Cols = table_Schema_for_Append.num_cols;
//     for (int i = 0; i<num_Cols; i++) {
//         col_data_type_t dt = table_Schema_for_Append.column_data[i].data_type;
//         switch (dt) {
//             case INT:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<int>(tokens[i+3])}
//                 );
//             case UNSIGNED_INT:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<unsigned int>(tokens[i+3])}
//                 );
//             case STRING:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<string>(tokens[i+3])}
//                 );
//             case BOOLEAN:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<bool>(tokens[i+3])}
//                 );
//             case FLOATING_POINT:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<float>(tokens[i+3])}
//                 );
//             case DOUBLE_FLOATING_POINT:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<double>(tokens[i+3])}
//                 );
//             case UNSIGNED_CHAR:
//                 data.push_back(
//                     (row_data_t){(unsigned char)i, make_shared<unsigned char>(tokens[i+3])}
//                 );
//             case NULL_TYPE:

//         }

//     }

//     int result = append_record_to_table(table_Schema_for_Append, data);

//     if (result == 0) {
//         printf("row insertion successful! \n");
//     } else {
//         printf("error! \n");
//     }
// }

// INSERT INTO table_name
// VALUES (value1, value2, value3, ...);
void insert_into_table(vector<string> tokens)
{
    string table_name = tokens[2]+"__schema_data.bin";
    schema_t new_schema = get_schema_from_schema(table_name);
    //   string table=tokens[2];
    // schema_t new_schema = get_schema_from_schema(table+"__schema_data.bin");
    // for (size_t i = 0; i < new_schema.num_cols; i++)
    // {
    //     cout << new_schema.column_data[i].is_primary_key << " ";
    //     cout << (int)new_schema.column_data[i].col_id << " ";
    //     cout << (int)new_schema.column_data[i].data_type << " ";
    //     cout << new_schema.column_data[i].col_name << " ";
    //     cout << new_schema.column_data[i].is_string << " ";
    //     cout << new_schema.column_data[i].max_str_len << " ";
    //     cout << endl;
    // }
    size_t num_cols = new_schema.num_cols;
    vector<row_data_t> data_to_insert;
    auto j = tokens.begin() + 5;
    for (size_t i = 0; i < num_cols; i++)
    {

        string value = *j;
        cout << "Column " << i
     << " datatype = "
     << (int)new_schema.column_data[i].data_type<<" ID= "<<(int)new_schema.column_data[i].col_id
     << endl;
        switch (new_schema.column_data[i].data_type)
        {
        case INT:
        {
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<int>(stoi(value))});
            j += 2;
            break;
        }

        case UNSIGNED_INT:
        {
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<unsigned int>(stoul(value))});
            j += 2;
            break;
        }

        case STRING:
        {
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<string>(value)});
            j += 2;
            break;
        }

        case BOOLEAN:
        {
            bool v = (value == "true");
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<bool>(v)});
            j += 2;
            break;
        }

        case FLOATING_POINT:
        {
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<float>(stof(value))});
            j += 2;
            break;
        }

        case DOUBLE_FLOATING_POINT:
        {
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<double>(stod(value))});
            j += 2;
            break;
        }
        case UNSIGNED_CHAR:
        {
            unsigned char v = static_cast<unsigned char>(stoi(value));
            data_to_insert.push_back(
                (row_data_t){static_cast<unsigned char>(i), make_shared<unsigned char>(v)});
            j += 2;
            break;
        }

        case NULL_TYPE:
        {
            data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<string>("NULL")});
            j += 2;
            break;
        }

        default:
        {
            logger("Unknown data type\n", LOG_ERROR);
            return;
        }
        }
    }
    int result = append_record_to_table(new_schema, data_to_insert);

    if (result == 0)
    {
        printf("row insertion successful! \n");
    }
    else
    {
        printf("error! \n");
    }
}