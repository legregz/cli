#include "../inc/element.hpp"
#include "../inc/functions.h"
#include <iostream>

void Element::set_minimal_size(SIZE minimal_size) {
	this->content_size = {minimal_size.w - border.l - border.r - padding.l - padding.r, minimal_size.h - border.t - border.b - padding.t - padding.b};
}

void Element::set_content_size(SIZE content_size) {
	this->content_size = content_size;
}

Element::Element() : foreground(WHITE), background(BLACK), expandable{true, false}, size{0, 1}, position{1, 1}, border{0, 0, 0, 0}, padding{0, 0, 0, 0}, alignment{'l', 't'}, content_size({0, 0}) {}

COLOR Element::get_foreground() const {
	return foreground;
}

COLOR Element::get_background() const {
	return background;
}

EXPANDABLE Element::get_expandable() const {
	return expandable;
}

SIZE Element::get_size() const {
	return {get_width(), get_height()};
}

int Element::get_width() const {
	return size.w + border.l + border.r + padding.l + padding.r;
}

int Element::get_height() const {
	return size.h + border.t + border.b + padding.t + padding.b;
}

SIZE Element::get_minimal_size() const {
	return {get_minimal_width(), get_minimal_height()};
}

int Element::get_minimal_width() const {
	return content_size.w + border.l + border.r + padding.l + padding.r;
}

int Element::get_minimal_height() const {
	return content_size.h + border.t + border.b + padding.t + padding.b;
}

SIZE Element::get_content_size() const {
	return content_size;
}

int Element::get_content_width() const {
	return content_size.w;
}

int Element::get_content_height() const {
	return content_size.h;
}

POSITION Element::get_position() const {
	return {position.x - border.l - padding.l, position.y - border.t - padding.t};
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

POSITION Element::get_content_position(SIZE content_size) const {
	if (content_size.w == 0 && content_size.h == 0) {
		content_size = this->content_size;
	};

	POSITION pos = {0, 0};

	switch (alignment.w) {
		case CENTER:
			pos.x = size.w / 2 - content_size.w / 2;
			break;
		case RIGHT:
			pos.x = size.w - content_size.w;
			break;
	}
	switch (alignment.h) {
		case CENTER:
			pos.y = size.h / 2 - content_size.h / 2;
			break;
		case BOTTOM:
			pos.y = size.h - content_size.h;
			break;
	}

	return {position.x + (pos.x >= 0 ? pos.x : 0), position.y + (pos.y >= 0 ? pos.y : 0)};
}

void Element::set_foreground(const COLOR& foreground) {
	this->foreground = foreground;
}

void Element::set_foreground_r(const COLOR& foreground) {
	set_foreground(foreground);
}

void Element::set_background(const COLOR& background) {
	this->background = background;
}

void Element::set_background_r(const COLOR& background) {
	set_background(background);
}

void Element::set_expandable(const EXPANDABLE& expandable) {
	this->expandable = expandable;
}

void Element::set_size(const SIZE& size) {
	set_width(size.w);
	set_height(size.h);
}

void Element::update_size() {}

void Element::set_width(int width) {
	size.w = width - border.l - border.r - padding.l - padding.r;
}

void Element::set_height(int height) {
	size.h = height - border.t - border.b - padding.t - padding.b;
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

void Element::show() const {
	cout << "\e[38;2;" << (int)foreground.r << ";" << (int)foreground.g << ";" << (int)foreground.b << 'm'<< "\e[48;2;" << (int)background.r << ";" << (int)background.g << ";" << (int)background.b << 'm';
	POSITION pos = get_position(); // with border and padding
	SIZE size_padding = {size.w + padding.r + padding.l, size.h + padding.t + padding.b};
	POSITION opposite_position_padding = {position.x + size.w + padding.r, position.y + size.h + padding.b};

	if (border.l) {
		if (border.t) {
			cout << "\e[" << pos.y << ";" << pos.x << "f┌";
		}
		for (int y = 0 - padding.t; y < size.h + padding.b; y++) {
			cout << "\e[" << position.y + y << ";" << pos.x << "f│";
		}
		if (border.b) {
			cout << "\e[" << opposite_position_padding.y << ";" << pos.x << "f└";
		}
	}
	if (border.r) {
		if (border.t) {
			cout << "\e[" << pos.y << ";" << opposite_position_padding.x << "f┐";
		}
		for (int y = 0 - padding.t; y < size.h + padding.b; y++) {
			cout << "\e[" << position.y + y << ";" << opposite_position_padding.x << "f│";
		}
		if (border.b) {
			cout << "\e[" << opposite_position_padding.y << ";" << opposite_position_padding.x << "f┘";
		}
	}
	if (border.t) {
		for (int x = 0 - padding.l; x < size.w + padding.r; x++) {
			cout << "\e[" << pos.y << ";" << position.x + x << "f─";
		}
	}
	if (border.b) {
		for (int x = 0 - padding.l; x < size.w + padding.r; x++) {
			cout << "\e[" << opposite_position_padding.y << ";" << position.x + x << "f─";
		}
	}

	for (int y = 0 - padding.t; y < size.h + padding.b; y++) {
		cout << "\e[" << position.y + y << ";" << position.x - padding.l << 'f';
		prints(size_padding.w);
	}
}
