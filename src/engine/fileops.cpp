#include<engine/fileops.h>


FILE* get_open_file_buffer(string file_name) {
    FILE* file_buffer = NULL;
    file_buffer = fopen(file_name.c_str(), "wb+");
    return file_buffer;
}