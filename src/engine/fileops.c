#include<engine/fileops.h>


FILE* get_open_file_buffer(char* file_name) {
    FILE* file_buffer = NULL;
    file_buffer = fopen(file_name, "wb+");
    return file_buffer;
}

void play_around(){
    FILE* file = get_open_file_buffer("data.bin");

    if (file){
        int arr[2] = {15,16};
        fwrite(&arr, sizeof(int), 2, file);
        logger("[written]\n", LOG_SUCCESS);

        fclose(file);
    } else {
        logger("[ERR] file doesn't exist\n", LOG_ERROR);
    }
}