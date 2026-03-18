#include <interpreter/interpreter.h>

void display_tables() {
    namespace fs = filesystem;
    string suffix = "__schema_data.bin";
    bool k = false;
    printf("displaying tables... \n");
//__schema_data.bin is created for every table whether or not data exists in it
//but _table_data is created only when data is inserted
//so, we use schema files to get names of the tables
    try {
        for (const auto &e : fs::directory_iterator(".")) { //"." refers to the path of the current working direcotry
            string f = e.path().filename().string();
            if (f.size() > suffix.size() && f.compare(f.size() - suffix.size(), suffix.size(), suffix) == 0) {
                string tableName = f.substr(0, f.size() - suffix.size());
                cout << "> " << tableName << endl;
                k = true;
            }
        }
    } catch (const fs::filesystem_error &error) {
        cerr << "Error accessing directory: " << error.what() << endl;
    }

    if (!k) {
        cout << "no tables..." << endl;
    }
}