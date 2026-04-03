#include "interpreter/interpreter.h"

const vector<string> keywards = {
    "create", "table", ";", "insert", "into", "set", "select"
};

bool is_valid_table_name(const string &s)
{
    string lower_name = s;

    for (int i=0; i<(int)s.size(); i++){
        lower_name[i] = (char)tolower(s[i]);
    }

    for (auto keyward: keywards) {
        if (keyward == lower_name) return false;
    }

    if (s.empty() || !(isalpha(s[0]) || s[0] == '_'))
        return false;

    for (size_t i = 1; i < s.size(); i++)
        if (!(isalnum(s[i]) || s[i] == '_'))
            return false;

    return true;
}