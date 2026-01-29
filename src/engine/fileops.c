#include<engine/fileops.h>


FILE* get_open_file_buffer(char* file_name){
    // Get the limit for the current system (or use a default 4096)
    long limit = pathconf("/", _PC_PATH_MAX);
    size_t size = (limit <= 0) ? 4096 : (size_t)limit;

    char *exe_path = malloc(size);
    char *full_path = malloc(size);

    ssize_t len = readlink("/proc/self/exe", exe_path, size - 1);
    FILE* file_buffer = NULL;

    if (len != -1) {
        exe_path[len] = '\0';
        
        char *dir = dirname(exe_path);
        
        // bin/../data/yourfile.bin
        snprintf(full_path, size, "%s/../data/%s", dir, file_name);

        file_buffer = fopen(full_path, "wb+");
    }

    free(exe_path);
    free(full_path);    

    if (file_buffer == NULL) logger("[ERR] file not created\n", LOG_ERROR);

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