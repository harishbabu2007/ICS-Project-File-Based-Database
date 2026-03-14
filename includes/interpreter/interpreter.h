#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <bits/stdc++.h>
using namespace std;

vector<string> tokenize(const string& s);
bool is_identifier(const string& s);
bool is_number(const string& s);
void create_table(vector<string>tokens);
void insert_into_table(vector<string> tokens);
void read_table(vector<string> tokens);
void delete_row(vector<string> tokens);

#endif