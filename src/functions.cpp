#include <iostream>
#include <termios.h>
#include <unistd.h>
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

struct termios original_termios;

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void enable_raw_mode() {
	if (tcgetattr(STDIN_FILENO, &original_termios) == -1) {
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}

	atexit(disable_raw_mode);

	struct termios raw = original_termios;

	raw.c_lflag &= ~(ECHO | ICANON | ISIG);

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}
