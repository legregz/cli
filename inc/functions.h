#pragma once

#include <cstdint>
#include <string>

using namespace std;

void init();

void spaces(int nb);

void printl(string text, int size);

int set_str_from_file(FILE* file, string* string, char separator);
