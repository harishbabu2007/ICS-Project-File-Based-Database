#include<stdio.h>
#include"utils/logging.h"
#include<engine/fileops.h>


void sample_testing(){
    logger("Test info\n", LOG_INFO);
    logger("Test success\n", LOG_SUCCESS);
    logger("Test error\n", LOG_ERROR);
    logger("Test warning\n", LOG_WARNING);

    char* columns[2] = {"Name", "Email"};
    char* rows[4] = {
        "John Doe", "b25xx10xx@iitj.ac.in",
        "Ben Dover", "b24yy101x@iitj.ac.in",
    };

    log_table_t *sample_table = new_log_table(
        2,
        2,
        columns,
        rows
    );

    log_table(sample_table);
}

int main(){
    play_around();
    // sample_testing();

    return 0;
}