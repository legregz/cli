#include "../inc/element.hpp"
#include "../inc/functions.h"
#include <iostream>

void Element::set_minimal_size(SIZE minimal_size) {
	this->minimal_size = {minimal_size.w - border.l - border.r - padding.l - padding.r, minimal_size.h - border.t - border.b - padding.t - padding.b};
}

Element::Element() : color(WHITE), background_color(BLACK), expandable(EXPANDABLE), size{0, 1}, position{1, 1}, border{0, 0, 0, 0}, padding{0, 0, 0, 0}, alignment{'l', 't'}, minimal_size({0, 1}) {}

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

SIZE Element::get_minimal_size() const {
	return {get_minimal_width(), get_minimal_height()};
}

int Element::get_minimal_width() const {
	return minimal_size.w + border.l + border.r + padding.l + padding.r;
}

int Element::get_minimal_height() const {
	return minimal_size.h + border.t + border.b + padding.t + padding.b;
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

ALIGNMENT Element::get_alignment() const {
	return alignment;
}

void Element::set_color(const COLOR& color) {
	this->color = color;
}

void Element::set_color_r(const COLOR& color) {
	set_color(color);
}

void Element::set_background_color(const COLOR& color) {
	this->background_color = color;
}

void Element::set_background_color_r(const COLOR& color) {
	set_background_color(color);
}

void Element::set_expandable(bool expandable) {
	this->expandable = expandable;
}

void Element::set_size(const SIZE& size) {
	set_width(size.w);
	set_height(size.h);
	update_size();
}

void Element::update_size() {}

void Element::set_width(int width) {
	size.w = width - border.l - border.r - padding.l - padding.r;
	update_size();
}

void Element::set_height(int height) {
	size.h = height - border.t - border.b - padding.t - padding.b;
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

void Element::set_alignment(const ALIGNMENT& alignment) {
	this->alignment = alignment;
}

// unique_ptr<Element> Element::clone() const {return nullptr;}

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

	pos = {0, 0};
	switch (alignment.w) {
		case CENTER:
			pos.x = size.w / 2 - minimal_size.w / 2;
			break;
		case RIGHT:
			pos.x = size.w - minimal_size.w;
			break;
	}
	switch (alignment.h) {
		case CENTER:
			pos.y = size.h / 2 - minimal_size.h / 2;
			break;
		case BOTTOM:
			pos.y = size.h - minimal_size.h;
			break;
	}

	cout << "\e[" << position.y + (pos.y >= 0 ? pos.y : 0) << ";" << position.x + (pos.x >= 0 ? pos.x : 0) << 'f';
	// cout << "\e[" << position.y << ";" << position.x << 'f';
}
