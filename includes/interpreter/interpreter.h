#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "engine/engine.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define init_max_query_length 100


int index_fromtable(char **a, int count);
int index_selectdata(char **a, int count);
int index_createtable(char **a, int count);
int index_insertinto(char **a, int count);

void interpreter_testing();
#endif