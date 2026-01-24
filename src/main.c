#include<stdio.h>
#include"logging/logging.h"


int main(){
    logger("Hello world\n", LOG_INFO);
    logger("Hello world\n", LOG_SUCCESS);
    logger("Hello world\n", LOG_ERROR);
    logger("Hello world\n", LOG_WARNING);
    return 0;
}