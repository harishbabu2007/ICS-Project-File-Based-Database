#ifndef FILEOPS_H
#define FILEOPS_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#include <string.h>

#define PLATFORM "linux"

void play_around();

FILE* get_open_file_buffer(char* file_name);

#endif