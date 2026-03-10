#include "interpreter/interpreter.h"
#include "engine/TableCreate.h"
#include "engine/TableWrite.h"
#include "engine/TableRead.h"

void create_table(vector<string> tokens)
{
    unsigned char column_id = 0;
    vector<col_item_t> column_data;

    unordered_map<string, col_data_type_t> type_map = {
        {"INT", INT},
        {"UNSIGNED_INT", UNSIGNED_INT},
        {"STRING", STRING},
        {"BOOLEAN", BOOLEAN},
        {"FLOATING_POINT", FLOATING_POINT},
        {"DOUBLE_FLOATING_POINT", DOUBLE_FLOATING_POINT},
        {"UNSIGNED_CHAR", UNSIGNED_CHAR},
        {"NULL_TYPE", NULL_TYPE}};

    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == "," || tokens[i] == "(" || tokens[i] == ")" || is_number(tokens[i]))
            continue;
        int check = -1;
        if (type_map.count(tokens[i]))
        {
            col_item_t col{};

            col.col_id = column_id;
            col.data_type = type_map[tokens[i]];
            col.col_name = tokens[i - 1];

            col.is_string = (col.data_type == STRING);

            col.is_primary_key = false;
            if (i + 1 < tokens.size() && tokens[i + 1] == "PRIMARY_KEY")
            {
                col.is_primary_key = true;
                if (i + 3 < tokens.size() && is_number(tokens[i + 3]))
                {
                    col.max_str_len = stoi(tokens[i + 3]);
                    check = 0;
                }
            }
            if (check != 0)
            {
                col.max_str_len = 0;
                if (i + 2 < tokens.size() && is_number(tokens[i + 2]))
                    col.max_str_len = stoi(tokens[i + 2]);
            }

            column_data.push_back(col);
            column_id++;
        }
    }

    // Building schema
    schema_t new_schema;
    new_schema.table_name = tokens[2];
    new_schema.num_cols = (int)column_data.size();
    new_schema.num_rows = 0;
    new_schema.column_data = column_data;

    // Creating the table
    int result = create_new_table_schema(new_schema);

    if (result != -1)
        logger("Successfully created schema\n", LOG_SUCCESS);
    else
        logger("Error in creating schema!\n", LOG_ERROR);
    // checking
    // string table=tokens[2];
    // schema_t table_schema = get_schema_from_schema(table+"__schema_data.bin");
    // for (size_t i = 0; i < table_schema.num_cols; i++)
    // {
    //     cout << table_schema.column_data[i].is_primary_key << " ";
    //     cout << (int)table_schema.column_data[i].col_id << " ";
    //     cout << table_schema.column_data[i].data_type << " ";
    //     cout << table_schema.column_data[i].col_name << " ";
    //     cout << table_schema.column_data[i].is_string << " ";
    //     cout << table_schema.column_data[i].max_str_len << " ";
    //     cout << endl;
    // }

    // Make sure inserted data matches number of columns
    // if (new_schema.num_cols < 3)
    // {
    //     logger("Not enough columns to insert test data\n", LOG_ERROR);
    //     return;
    // }

    // vector<row_data_t> data_to_insert1 = {
    //     {0, make_shared<int>(0)},
    //     {1, make_shared<string>("b25ee1009")},
    //     {2, make_shared<string>("Ashhar Ansari")},
    //     {3, make_shared<string>("Electrical Engineering")}};

    // vector<row_data_t> data_to_insert_2 = {
    //     {0, make_shared<int>(1)},
    //     {1, make_shared<string>("b25ee1001")},
    //     {2, make_shared<string>("Abhishek Reddy")},
    //     {3, make_shared<string>("Computer Science")}

    // };

    // vector<row_data_t> data_to_insert_3 = {
    //     {0, make_shared<int>(2)},
    //     {1, make_shared<string>("b25bb1002")},
    //     {2, make_shared<string>("Harish Babu Balaji")},
    //     {3, make_shared<string>("Bioengineering")}};
    // vector<row_data_t> data_to_insert_4 = {
    //     {0, make_shared<int>(3)},
    //     {1, make_shared<string>("b25me1002")},
    //     {2, make_shared<string>("Rahul")},
    //     {3, make_shared<string>("Mechanical")}};
    // int res1 = append_record_to_table(new_schema, data_to_insert1);
    // int res2 = append_record_to_table(new_schema, data_to_insert_2);
    // int res3 = append_record_to_table(new_schema, data_to_insert_3);
    // int res4 = append_record_to_table(new_schema, data_to_insert_4);
    // if (res1 == 0 && res2 == 0 && res3 == 0 && res4 == 0)
    //     logger("Successfully Written Data\n", LOG_SUCCESS);
    // else
    //     logger("Error in writing data!\n", LOG_ERROR);
    // // }
}