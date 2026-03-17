#include <interpreter/interpreter.h>

void display_tables() {
    namespace fs = std::filesystem;
    std::string suffix = "__schema_data.bin";
    bool k = false;
    printf("displaying tables... \n");
//__schema_data.bin is created for every table whether or not data exists in it
//but _table_data is created only when data is inserted
//so, we use schema files to get names of the tables
    try {
        for (const auto &entry : fs::directory_iterator(".")) { //"." refers to the path of the current working direcotry
            std::string filename = entry.path().filename().string();
            if (filename.size() > suffix.size() && filename.compare(filename.size() - suffix.size(), suffix.size(), suffix) == 0) {
                std::string tableName = filename.substr(0, filename.size() - suffix.size());
                std::cout << "> " << tableName << std::endl;
                k = true;
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    if (!k) {
        std::cout << "no tables..." << std::endl;
    }
}