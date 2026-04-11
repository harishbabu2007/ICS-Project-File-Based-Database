#include "interpreter/interpreter.h"
#include "engine/TableRead.h"

void check_selectData(vector<string> tokens, vector<string> lower_tok)
{
    int l = tokens.size();

    // Basic length and syntax check (min: SELECT * FROM table ;)
    if (l < 5)
    {
        printf("Error: Incomplete SELECT statement.\n");
        return;
    }

    if (lower_tok[0] != "select" || tokens[l - 1] != ";")
    {
        printf("Error: Syntax error. Expected format: SELECT col1, col2 FROM tableName ;\n");
        return;
    }

    // Finding the FROM keyword
    int fromIdx = -1;
    for (int i = 1; i < l - 1; i++)
    {
        if (lower_tok[i] == "from")
        {
            fromIdx = i;
            break;
        }
    }

    if (fromIdx == -1)
    {
        printf("Error: Syntax error. Missing 'FROM' keyword.\n");
        return;
    }
    if (fromIdx == 1)
    {
        printf("Error: Syntax error. Missing columns to select.\n");
        return;
    }

    // Extract and check the requested columns
    vector<string> selected_cols;
    if (fromIdx == 2 && tokens[1] == "*")
    {
        selected_cols.push_back("*");
    }
    else
    {
        for (int i = 1; i < fromIdx; i++)
        {
            if (tokens[i] != ",")
            {
                selected_cols.push_back(tokens[i]);
            }
            else
            {
                // Ensure no consecutive commas or trailing commas before FROM
                if (i == 1 || i == fromIdx - 1 || tokens[i - 1] == ",")
                {
                    printf("Error: Syntax error in column list.\n");
                    return;
                }
            }
        }
    }

    // getting the table name
    if (fromIdx >= l - 2)
    {
        printf("Error: Syntax error. Missing table name after FROM.\n");
        return;
    }
    string tbName = tokens[fromIdx + 1];

    // Checking if the table exists
    string schemaName = tbName + "__schema_data.bin";
    schema_t schema = get_schema_from_schema(schemaName);

    if (schema.num_cols == 0)
    {
        printf("Error: Table '%s' does not exist.\n", tbName.c_str());
        return;
    }

    // checking if the requested columns actually exist in the schema
    if (selected_cols[0] != "*")
    {
        for (size_t i = 0; i < selected_cols.size(); i++)
        {
            bool found = false;
            for (int c = 0; c < schema.num_cols; c++)
            {
                if (schema.column_data[c].col_name == selected_cols[i])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                printf("Error: Column '%s' does not exist in table '%s'.\n", selected_cols[i].c_str(), tbName.c_str());
                return;
            }
        }
    }

    // Check WHERE clause (if present)
    int whereIdx = -1;
    for (int i = fromIdx + 2; i < l - 1; i++)
    {
        if (lower_tok[i] == "where")
        {
            whereIdx = i;
            break;
        }
    }

    if (whereIdx != -1)
    {
        // Syntax should be WHERE ID = value ;
        if (whereIdx != l - 5 || tokens[whereIdx + 2] != "=")
        {
            printf("Error: Syntax error in WHERE clause. Expected format: WHERE ID = value ;\n");
            return;
        }

        string whereColName = tokens[whereIdx + 1];
        string whereVal = tokens[whereIdx + 3];

        // only id can be given in where clause
        string lowerWhereCol = "";
        for (char c : whereColName)
            lowerWhereCol += tolower(c);

        if (lowerWhereCol != "id")
        {
            printf("Error: Unsupported WHERE condition. Only 'ID' is allowed.\n");
            return;
        }

        // finding the ID column in the schema
        int colIdx = -1;
        for (int c = 0; c < schema.num_cols; c++)
        {
            string lowerSchemaCol = "";
            for (size_t iter = 0; iter < schema.column_data[c].col_name.size(); iter++)
                lowerSchemaCol += (char)tolower(schema.column_data[c].col_name[iter]);

            if (lowerSchemaCol == "id")
            {
                colIdx = c;
                break;
            }
        }

        if (colIdx == -1)
        {
            printf("Error: Column 'ID' does not exist in table '%s'.\n", tbName.c_str());
            return;
        }
        else
        {
            string rowIDnum = tokens[l - 2];
            for (size_t it = 0; it < rowIDnum.size(); it++)
            {
                if (rowIDnum[it] < '0' || rowIDnum[it] > '9')
                {
                    printf("Error: invalid ID Number \n");
                    return;
                }
            }
            int colID = stoi(rowIDnum);
            if (colID >= schema.num_rows)
            {
                printf("Error: Row ID out of bounds \n");
                return;
            }
        }
    }
    else
    {
        // If there is no WHERE clause, there shouldn't be anything between the table name and ';'
        if (fromIdx + 2 != l - 1)
        {
            printf("Error: Syntax error near '%s'.\n", tokens[fromIdx + 2].c_str());
            return;
        }
    }

    // executing the function if all checks are passed
    read_table(tokens);
}