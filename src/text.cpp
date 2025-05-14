#include "../inc/text.hpp"
// #include "../inc/clonableelement.hpp"
#include "../inc/functions.h"
#include <iostream>

// template class ClonableElement<Text>;

Text::Text() : alignment{'l', 't'} {}//set_expandable(H_EXPANDABLE);}

const ALIGNMENT Text::get_alignment() const {
	return alignment;
}

const string& Text::get_text() const {
	return text;
}

void Text::set_alignment(const ALIGNMENT& alignment) {
	this->alignment = alignment;
}

void Text::set_text(const string& text) {
	this->text = text;
	size.w = text.size();
}

void Text::show() const {
	Element::show();
	POSITION pos = {0, 0};
	switch (alignment.w) {
		case CENTER:
			pos.x = size.w / 2 - text.size() / 2;
			break;
		case RIGHT:
			pos.x = size.w - text.size();
			break;
	}
	switch (alignment.h) {
		case CENTER:
			pos.y = size.h / 2;
			break;
		case BOTTOM:
			pos.y = size.h - 1;
			break;
	}

	cout << "\e[" << position.y + (pos.y >= 0 ? pos.y : 0) << ";" << position.x + (pos.x >= 0 ? pos.x : 0) << 'f';
	printl(text, size.w);
	cout << normal;
}
