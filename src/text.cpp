#include "../inc/text.hpp"
// #include "../inc/clonableelement.hpp"
#include "../inc/functions.h"
#include <iostream>

// template class ClonableElement<Text>;

Text::Text() : text(""), style(NORMAL) {set_expandable({false, false});}

const string& Text::get_text() const {
	return text;
}

void Text::set_text(const string& text) {
	this->text = text;
	minimal_size.w = text.size();
}

void Text::show() const {
	// cout << style;
	// AlignableElement::show({(int)text.size(), 1});
	Element::show();

	POSITION pos = get_content_position();
	cout << "\e[" << pos.y << ";" << pos.x << 'f';

	printl(text, size.w);
	cout << NORMAL;
}
