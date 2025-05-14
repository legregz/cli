#include "../inc/element.hpp"
#include "../inc/functions.h"
#include <iostream>

Element::Element() : color(white), background_color(black), expandable(EXPANDABLE), size{0, 1}, position{1, 1}, border{0, 0, 0, 0}, padding{0, 0, 0, 0} {}

COLOR Element::get_color() const {
	return color;
}

COLOR Element::get_background_color() const {
	return background_color;
}

bool Element::get_expandable() const {
	return expandable;
}

SIZE Element::get_size() const {
	return {get_width(), get_height()};
	// return {size.w + border.l + border.r, size.h + border.t + border.b};
}

int Element::get_width() const {
	return size.w + border.l + border.r + padding.l + padding.r;
	// return size.w + border.l + border.r;
}

int Element::get_height() const {
	return size.h + border.t + border.b + padding.t + padding.b;
	// return size.h + border.t + border.b;
}

POSITION Element::get_position() const {
	return {position.x - border.l, position.y - border.t};
}

BORDER Element::get_border() const {
	return border;
}

PADDING Element::get_padding() const {
	return padding;
}

void Element::set_color(const COLOR& color) {
	this->color = color;
}

void Element::set_background_color(const COLOR& color) {
	this->background_color = color;
}

void Element::set_expandable(bool expandable) {
	this->expandable = expandable;
}

void Element::set_size(const SIZE& size) {
	// set_width(size.w);
	// set_height(size.h);
	this->size = {size.w - border.l - border.r - padding.l - padding.r, size.h - border.t - border.b - padding.t - padding.b};
	update_size();
}

void Element::update_size() {}

void Element::set_width(int width) {
	size.w = width - border.l - border.r - padding.l - padding.r;
	// size.w = width - border.l - border.r;
	update_size();
}

void Element::set_height(int height) {
	size.h = height - border.t - border.b - padding.t - padding.b;
	// size.h = height - border.t - border.b;
	update_size();
}

void Element::set_position(const POSITION& position) {
	this->position = {position.x + border.l + padding.l, position.y + border.t + padding.t};
}

void Element::set_border(const BORDER& border) {
	this->border = border;
}

void Element::set_padding(const PADDING& padding) {
	this->padding = padding;
}

void Element::show() const {
	cout << "\e[38;2;" << (int)color.r << ";" << (int)color.g << ";" << (int)color.b << 'm'<< "\e[48;2;" << (int)background_color.r << ";" << (int)background_color.g << ";" << (int)background_color.b << 'm';
	POSITION pos = get_position(); // with border

	if (border.l) {
		if (border.t) {
			cout << "\e[" << pos.y << ";" << pos.x << "f┌";
		}
		for (int y = 0; y < size.h; y++) {
			cout << "\e[" << position.y + y << ";" << pos.x << "f│";
		}
		if (border.b) {
			cout << "\e[" << position.y + size.h << ";" << pos.x << "f└";
		}
	}
	if (border.r) {
		if (border.t) {
			cout << "\e[" << pos.y << ";" << position.x + size.w << "f┐";
		}
		for (int y = 0; y < size.h; y++) {
			cout << "\e[" << position.y + y << ";" << position.x + size.w << "f│";
		}
		if (border.b) {
			cout << "\e[" << position.y + size.h << ";" << position.x + size.w << "f┘";
		}
	}
	if (border.t) {
		for (int x = 0; x < size.w; x++) {
			cout << "\e[" << pos.y << ";" << position.x + x << "f─";
		}
	}
	if (border.b) {
		for (int x = 0; x < size.w; x++) {
			cout << "\e[" << position.y + size.h << ";" << position.x + x << "f─";
		}
	}

	for (int y = 0; y < size.h; y++) {
		cout << "\e[" << position.y + y << ";" << position.x << 'f';
		prints(size.w);
	}
}
