#include "../inc/alignableelement.hpp"
#include <iostream>

AlignableElement::AlignableElement() : alignment{'l', 't'} {}

const ALIGNMENT AlignableElement::get_alignment() const {
	return alignment;
}

void AlignableElement::set_alignment(const ALIGNMENT& alignment) {
	this->alignment = alignment;
}

void AlignableElement::show(const SIZE element_minimal_size) const {
	Element::show();
	POSITION pos = {0, 0};
	switch (alignment.w) {
		case CENTER:
			pos.x = size.w / 2 - element_minimal_size.w / 2;
			break;
		case RIGHT:
			pos.x = size.w - element_minimal_size.w;
			break;
	}
	switch (alignment.h) {
		case CENTER:
			pos.y = size.h / 2 - element_minimal_size.h / 2;
			break;
		case BOTTOM:
			pos.y = size.h - 1 - element_minimal_size.h;
			break;
	}

	cout << "\e[" << position.y + (pos.y >= 0 ? pos.y : 0) << ";" << position.x + (pos.x >= 0 ? pos.x : 0) << 'f';
}
