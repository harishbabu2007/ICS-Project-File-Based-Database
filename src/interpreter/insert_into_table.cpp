#include "interpreter/interpreter.h"
#include "engine/TableWrite.h"
#include "engine/TableRead.h"

// void insert_into_table(vector<string> tokens)
// {
//     string table_name = tokens[2];
//     schema_t new_schema = get_schema_from_schema(table_name + "__schema_data.bin");
//     size_t num_cols = new_schema.num_cols;
//     vector<row_data_t> data_to_insert;
//     auto j = tokens.begin() + 5;
//     for (size_t i = 0; i < num_cols; i++)
//     {
//         string value = *j;
//         switch (new_schema.column_data[i].data_type)
//         {
//         case INT:
//         {
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<int>(stoi(value))});
//             j += 2;
//             break;
//         }

//         case UNSIGNED_INT:
//         {
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<unsigned int>(stoul(value))});
//             j += 2;
//             break;
//         }

//         case STRING:
//         {
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<string>(value)});
//             j += 2;
//             break;
//         }

//         case BOOLEAN:
//         {
//             bool v = (value == "true");
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<bool>(v)});
//             j += 2;
//             break;
//         }

//         case FLOATING_POINT:
//         {
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<float>(stof(value))});
//             j += 2;
//             break;
//         }

//         case DOUBLE_FLOATING_POINT:
//         {
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<double>(stod(value))});
//             j += 2;
//             break;
//         }
//         case UNSIGNED_CHAR:
//         {
//             unsigned char v = static_cast<unsigned char>(stoi(value));
//             data_to_insert.push_back(
//                 (row_data_t){static_cast<unsigned char>(i), make_shared<unsigned char>(v)});
//             j += 2;
//             break;
//         }

//         case NULL_TYPE:
//         {
//             data_to_insert.push_back((row_data_t){static_cast<unsigned char>(i), make_shared<string>("NULL")});
//             j += 2;
//             break;
//         }

//         default:
//         {
//             logger("Unknown data type\n", LOG_ERROR);
//             return;
//         }
//         }
//     }
//     int result = append_record_to_table(new_schema, data_to_insert);

//     if (result == 0)
//     {
//         printf("row insertion successful! \n");
//     }
//     else
//     {
//         printf("error! \n");
//     }
// }
void insert_into_table(vector<string> tokens)
{
    string table_name = tokens[2];
    schema_t new_schema = get_schema_from_schema(table_name + "__schema_data.bin");

    size_t num_cols = new_schema.num_cols;

    auto j = tokens.begin() + 4;

    while (j != tokens.end())
    {
        if (*j == "(")
        {
            j++;

            vector<row_data_t> data_to_insert;

            for (size_t i = 0; i < num_cols; i++)
            {
                string value = *j;

                switch (new_schema.column_data[i].data_type)
                {
                case INT:
                {
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<int>(stoi(value))});
                    break;
                }

                case UNSIGNED_INT:
                {
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<unsigned int>(stoul(value))});
                    break;
                }

                case STRING:
                {
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<string>(value)});
                    break;
                }

                case BOOLEAN:
                {
                    bool v = (value == "true");
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<bool>(v)});
                    break;
                }

                case FLOATING_POINT:
                {
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<float>(stof(value))});
                    break;
                }

                case DOUBLE_FLOATING_POINT:
                {
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<double>(stod(value))});
                    break;
                }

                case UNSIGNED_CHAR:
                {
                    unsigned char v = static_cast<unsigned char>(stoi(value));
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<unsigned char>(v)});
                    break;
                }

                case NULL_TYPE:
                {
                    data_to_insert.push_back(
                        {static_cast<unsigned char>(i), make_shared<string>("NULL")});
                    break;
                }

                default:
                {
                    logger("Unknown data type\n", LOG_ERROR);
                    return;
                }
                }

                j++; // move to next token

                if (*j == ",") // skip comma between values
                    j++;
            }

            int result = append_record_to_table(new_schema, data_to_insert);

            if (result != 0)
            {
                printf("error inserting row\n");
                return;
            }

            // move until next row or end
            while (j != tokens.end() && *j != "(")
                j++;
        }
        else
        {
            j++;
        }
    }

    printf("all rows inserted successfully!\n");
}