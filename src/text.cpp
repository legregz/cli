#include "../inc/text.hpp"
// #include "../inc/clonableelement.hpp"
#include "../inc/functions.h"
#include <iostream>

// template class ClonableElement<Text>;

Text::Text() : text(""), style(NORMAL) {set_expandable(NOT_EXPANDABLE);}//set_expandable(H_EXPANDABLE);}

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

	printl(text, size.w);
	cout << NORMAL;
}
