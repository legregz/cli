#include <iostream>
#include "../inc/functions.h"

void prints(int nb)
{
	string text;
	for (int i = 0; i < nb; i++)
	{
		text += ' ';
	}
	cout << text;
}

void printl(const string text, int size) {
	if (text.size() > size) {
		for (int i = 0; i < size - 3; i++)
			cout << text[i];
		cout << "...";
	}
	else
		cout << text;
}

int set_str_from_file(FILE* file, string* string, char separator) {
	char c;
	while ((c = fgetc(file)) != EOF && (c == '\n' || c == ' '));
	while(c != EOF && c != separator) {
		if (c != '\n')
			string->push_back(c);
		c = fgetc(file);
	}
	if (c == EOF)
		return 1;
	return 0;
}
