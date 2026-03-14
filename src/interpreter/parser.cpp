#include "interpreter/interpreter.h"

void parser() {
    printf("Welcome to our interpreter!!!\n");
    while (true) {
        printf("~$ ");
        string query;
        getline(cin, query);
        vector<string> tokens = tokenize(query);
        vector<string> lower_tok;
        int l = tokens.size();
        for (int i = 0; i<l; i++) {
            string s = tokens[i];
            string lower = "";
            int k = s.size();
            for (int j = 0; j<k; j++) {
                lower += (char) tolower((unsigned char) s[j]);
            }
            lower_tok.push_back(lower);
        }

        if (lower_tok[0] == "create" && lower_tok[1] == "table" && tokens[l-1] == ";" && tokens[3] == "(" && tokens[l-2] == ")") {
            int pk = 0;
            for (int i = 6; i<l-3; i++) {
                if (lower_tok[i] == "primary" && lower_tok[i+1] == "key") {
                    pk = 1;
                    break;
                }
            }
            
            int flag = 0;
            for (int i = 4; i<l-2; i++) {
                if (lower_tok[i] == "create" || lower_tok[i] == "table" || lower_tok[i] == ";" || lower_tok[i] == "insert" || lower_tok[i] == "into" || lower_tok[i] == "values" || lower_tok[i] == "select" || lower_tok[i] == "from" || lower_tok[i] == "where" || lower_tok[i] == "delete" || lower_tok[i] == "set") {
                    flag = 1;
                    break;
                }
            }

            if (pk == 0) {
                printf("Error: PRIMARY KEY not found! \n");
            }
            
            else if (flag == 1) {
                printf("Error: Attempt to insert to name column after Keyword! \n");
                printf("Keywords: \"CREATE, TABLE, INSERT, INTO, VALUES, SELECT, FROM, WHERE, DELETE, SET, ;\" \n");
            }

            else {
                create_table(tokens);
            }
        }
        
        else if (lower_tok[0] == "insert" && lower_tok[1] == "into" && lower_tok[3] == "values" && tokens[4] == "(" && tokens[l-2] == ")" && tokens[l-1] == ";") {
            int flag = 0;
            for (int i = 5; i<l-2; i++) {
                if (lower_tok[i] == "create" || lower_tok[i] == "table" || lower_tok[i] == ";" || lower_tok[i] == "insert" || lower_tok[i] == "into" || lower_tok[i] == "values" || lower_tok[i] == "select" || lower_tok[i] == "from" || lower_tok[i] == "where" || lower_tok[i] == "delete" || lower_tok[i] == "set") {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1) {
                printf("Error: Attempt to insert to insert Keyword! \n");
                printf("Keywords: CREATE, TABLE, INSERT, INTO, VALUES, SELECT, FROM, WHERE, DELETE, SET, ; \n");
            }

            else {
                insert_into_table(tokens);
            }
        }

        else if (lower_tok[0] == "select" && tokens[l-1] == ";") {
            int from = 0;
            for (int i = 2; i<l-2; i++) {
                if (lower_tok[i] == "from") {
                    from = 1;
                }
            }

            if (from == 0) {
                printf("Error: FROM not found! \n");
            }

            else {
                read_table(tokens);
            }
        }

        else {
            printf("Error: Check your syntax! \n");
        }
    }
}