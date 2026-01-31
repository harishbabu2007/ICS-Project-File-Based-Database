#ifndef FILEOPS_H
#define FILEOPS_H


#include <stdio.h>
#include <stdlib.h>
#include "utils/logging.h"

void play_around();

FILE* get_open_file_buffer(char* file_name);

#endif