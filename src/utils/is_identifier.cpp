#include "interpreter/interpreter.h"

bool is_identifier(const string &s)
{
    if (s.empty() || !(isalpha(s[0]) || s[0] == '_'))
        return false;

    for (size_t i = 1; i < s.size(); i++)
        if (!(isalnum(s[i]) || s[i] == '_'))
            return false;

    return true;
}