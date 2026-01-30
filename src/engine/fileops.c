#include<engine/fileops.h>


FILE* get_open_file_buffer(char* file_name) {
    FILE* file_buffer = NULL;
    char *exe_path = NULL;
    char *full_path = NULL;

#if defined(__linux__)
    long limit = pathconf("/", _PC_PATH_MAX);
    size_t size = (limit > 0) ? (size_t)limit : 4096;

    exe_path = malloc(size);
    if (!exe_path) goto error;

    ssize_t len = readlink("/proc/self/exe", exe_path, size - 1);
    if (len == -1) goto error;
    exe_path[len] = '\0';

#elif defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(NULL, &size);   // query size

    exe_path = malloc(size);
    if (!exe_path) goto error;

    if (_NSGetExecutablePath(exe_path, &size) != 0) goto error;
    exe_path = realpath(exe_path, NULL); // canonical absolute path
    if (!exe_path) goto error;
#else
#error "Unsupported OS"
#endif

    full_path = malloc(strlen(exe_path) + strlen(file_name) + 16);
    if (!full_path) goto error;

    char* dir = dirname(exe_path);
    snprintf(full_path, strlen(exe_path) + strlen(file_name) + 16, "%s/../data/%s", dir, file_name);

    file_buffer = fopen(full_path, "wb+");
    if (!file_buffer) goto error;

    free(exe_path);
    free(full_path);

    return file_buffer;
error:
    logger("[ERR] file not created\n", LOG_ERROR);
    free(exe_path);
    free(full_path);
    return NULL;
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