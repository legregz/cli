#include "../inc/text.hpp"
// #include "../inc/clonablecomponent.hpp"
#include "../inc/functions.h"
#include <iostream>

// template class ClonableComponent<Text>;

Text::Text() : text(""), style(NORMAL) {set_expandable({false, false});}

const string& Text::get_text() const {
	return text;
}

void Text::set_text(const string& text) {
	this->text = text;
	set_content_size({(int)text.size(), 1});
}

void Text::show() const {
	// cout << style;
	// AlignableComponent::show({(int)text.size(), 1});
	Component::show();

	POSITION pos = get_content_position();
	cout << "\e[" << pos.y << ";" << pos.x << 'f';

	printl(text, size.w);
	cout << NORMAL;
}
