#include "logging/logging.h"

void logger(char *buffer, log_status_t status){
    switch (status){
        case LOG_INFO:
            printf("%s", buffer);
            return;
        case LOG_SUCCESS:
            printf(ANSI_COLOR_GREEN "%s", buffer);
            return;
        case LOG_ERROR:
            printf(ANSI_COLOR_RED "%s", buffer);
            return;
        case LOG_WARNING:
            printf(ANSI_COLOR_YELLOW "%s", buffer);
            return;
        default:
            printf("%s", buffer);
    }

    printf("" ANSI_COLOR_RESET);
}