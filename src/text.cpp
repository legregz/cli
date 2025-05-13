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
	int posx = 0;
	switch (alignment) {
		case 'c':
			posx = size.w / 2 - text.size() / 2;
			break;
		case 'r':
			posx = size.w - text.size();
			break;
	}

	cout << "\e[" << position.y + size.h / 2 << ";" << position.x + (posx >= 0 ? posx : 0) << 'f';
	printl(text, size.w);
	cout << normal;
}
