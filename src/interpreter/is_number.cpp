#include "interpreter/interpreter.h"

bool is_number(const string& s) {
    for(char c : s) {
        if(!isdigit(c)) {
            return false;
        }
    }
    return true;
}