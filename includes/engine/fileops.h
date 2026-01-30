#ifndef FILEOPS_H
#define FILEOPS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#if defined(__linux__)
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <limits.h>
#endif
#include "utils/logging.h"

void play_around();

FILE* get_open_file_buffer(char* file_name);

#endif