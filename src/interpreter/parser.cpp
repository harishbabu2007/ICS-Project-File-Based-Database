#include "interpreter/interpreter.h"

void parser() {
    cout << "Welcome to our interpreter!!!" << endl;
    cout << "A project by Abhishek Reddy N, Ashhar Bashar Ansari, Harish Babu Balaji and Rahul Shreevatsavan R V" << endl;

    string ICS = R"(
  _____   _____   _____ 
 |_   _| / ____| / ____|
   | |  | |     | (___  
   | |  | |      \___ \
  _| |_ | |____  ____) |
 |_____| \_____||_____/ 
    )";

    cout << ICS << endl;
    cout << "======================================================" << endl;
    cout << " Database Command Line Interface v1.0.0" << endl;
    cout << " Type 'help' for available commands or 'exit' to quit" << endl;
    cout << "======================================================" << endl;

    while (true) {
        printf("~$ ");
        string query;
        getline(cin, query);
        
        vector<string> tokens = tokenize(query);
        vector<string> lower_tok;
        int l = tokens.size();

        // making lower case tokens
        for (int i=0; i<l; i++){
            string s = tokens[i];
            for (int j=0; j<(int)s.size(); j++){
                s[j] = (char)tolower(s[j]);
            }
            lower_tok.push_back(s);
        }

        if (lower_tok.size() == 1 && lower_tok[0] == "exit") {
            break;
        }

        else if (lower_tok.size() == 1 && lower_tok[0] == "help") {
            cout << "Available Commands:" << endl;
            cout << "  CREATE TABLE ... ;  - Create a new table" << endl;
            cout << "  INSERT INTO ... ;   - Insert a row into a table" << endl;
            cout << "  SELECT ... ;        - Query data from a table" << endl;
            cout << "  UPDATE ... ;        - Modify an existing row" << endl;
            cout << "  DELETE ... ;        - Remove a row" << endl;
            cout << "  DISPLAY TABLES ;    - List all available tables" << endl;
            cout << "  exit                - Exit" << endl;
        }

        else if (lower_tok[0] == "create" && lower_tok[1] == "table" && tokens[l-1] == ";" && tokens[3] == "(" && tokens[l-2] == ")") {
            check_createTable(tokens, lower_tok);
        }
        
        else if (lower_tok[0] == "insert" && lower_tok[1] == "into" && lower_tok[3] == "values" && tokens[4] == "(" && tokens[l-2] == ")" && tokens[l-1] == ";") {
            check_insertRow(tokens, lower_tok);
        }

        else if (lower_tok[0] == "select" && tokens[l-1] == ";") {
            check_selectData(tokens, lower_tok);
        }

        else if (lower_tok[0] == "delete" && lower_tok[l-3] == "from" && lower_tok[l-1] == ";" && lower_tok[l-4] == ")" && lower_tok[1] == "(") {
            check_deleteRow(tokens);
        }

        else if (lower_tok[0] == "update" && lower_tok[2] == "set" && lower_tok[l-5] == "where" && lower_tok[l-3] == "=" && lower_tok[l-1] == ";") {
            check_modifyRow(tokens, lower_tok);
        }

        else if (lower_tok[0] == "display" && lower_tok[1] == "tables" && lower_tok[2] == ";" && lower_tok.size() == 3) {
            display_tables();
        }

        else {
            printf("Error: Invalid Command! \n");
        }
    }
    return;
}