#include "../inc/text.hpp"
// #include "../inc/clonableelement.hpp"
#include "../inc/functions.h"
#include <iostream>

template class ClonableElement<Text>;

Text::Text() : alignment('l') {}//set_expandable(H_EXPANDABLE);}

const char Text::get_alignment() const {
	return alignment;
}

const string& Text::get_text() const {
	return text;
}

void Text::set_alignment(char alignment) {
	this->alignment = alignment;
}

void Text::set_text(const string& text) {
	this->text = text;
	size.w = text.size();
}

void Text::show() const {
	Element::show();
	cout << "\e[" << position.y + size.h / 2 << ";" << position.x << 'f';

	double nb_spaces;
	switch (alignment) {
		case 'l':
			printl(text, size.w);
			spaces(size.w - text.size());
			break;
		case 'c':
			nb_spaces = (size.w - text.size()) / 2.0;
			spaces(nb_spaces + (nb_spaces - (int)nb_spaces > 0 ? 1 : 0));
			printl(text, size.w);
			spaces(nb_spaces);
			break;
		case 'r':
			spaces(size.w - text.size());
			printl(text, size.w);
			break;
	}
	cout << normal;
}
