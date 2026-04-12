#include "interpreter/interpreter.h"
#include "engine/TableRead.h"

void check_selectData(vector<string> tokens, vector<string> lower_tok)
{
    int l = tokens.size();

    // Basic length and syntax check (min: SELECT * FROM table;)
    if (l < 5)
    {
        logger("Error: Incomplete SELECT statement.\n", LOG_ERROR);
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
        logger("Error: Syntax error. Missing 'FROM' keyword.\n", LOG_ERROR);
        return;
    }
    if (fromIdx == 1)
    {
        logger("Error: Syntax error. Missing columns to select.\n", LOG_ERROR);
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
                // There should be no unnecessary commas before FROM
                if (i == 1 || i == fromIdx - 1 || tokens[i - 1] == ",")
                {
                    logger("Error: Syntax error in column list.\n", LOG_ERROR);
                    return;
                }
            }
        }
    }

    // getting the table name
    if (fromIdx >= l - 2)
    {
        logger("Error: Syntax error. Missing table name after FROM.\n", LOG_ERROR);
        return;
    }
    string tbName = tokens[fromIdx + 1];

    // Checking if the table exists
    string schemaName = tbName + "__schema_data.bin";
    schema_t schema = get_schema_from_schema(schemaName);

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
                printf(ANSI_COLOR_RED "Error: Column '%s' does not exist in table '%s'." ANSI_COLOR_RESET "\n", selected_cols[i].c_str(), tbName.c_str());
                return;
            }
        }
    }

    // If there is no WHERE clause, there shouldn't be anything between the table name and ';'
    if (fromIdx + 2 != l - 1)
    {
        printf(ANSI_COLOR_RED "Error: Syntax error near '%s'." ANSI_COLOR_RESET "\n", tokens[fromIdx + 2].c_str());
        return;
    }

    // executing the function if all checks are passed
    read_table(tokens);
}