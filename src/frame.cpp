#include "../inc/frame.hpp"
// #include "../inc/clonableelement.hpp"
#include <memory>
#include <stdexcept>

// template class ClonableElement<Frame>;

Frame::Frame() : direction(DIRECTION_H), elements(vector<unique_ptr<Element>>()) {Element::set_size({0, 0});}

Frame::Frame(const Frame& other) {
	color = other.color;
	background_color = other.background_color;
	expandable = other.expandable;
	size = other.size;
	border = other.border;
	direction = other.direction;
	padding = other.padding;

	for (const auto& elt : other.elements) {
		elements.push_back(elt->clone());
	}
}

bool Frame::get_direction() const {
	return direction;
}

void Frame::add(Element& elt) {
	elements.push_back(elt.clone());
	if (!direction) {
		Element::set_size({size.w + elt.get_width(), size.h < elt.get_height() ? elt.get_height() : size.h});
	} else {
		Element::set_size({size.w < elt.get_width() ? elt.get_width() : size.w, size.h + elt.get_height()});
	}
}

void Frame::update_size() {
	// cout << "exp" << expandable << endl;

	// if (expandable) {
	// 	Element::set_size(size);
	// } // else if (size.w < this->size.w) {
	// 	Element::set_size({size.w, this->size.h});
	// }
	// 	int width = 0, elt_width;
	// 	if (!direction) {
	// 		for (auto& elt : elements) {
	// 			width += elt->get_size()[0];
	// 		}
	// 	} else {
	// 		for (auto& elt : elements) {
	// 			elt_width = elt->get_size()[0];
	// 			if (width < elt_width) {
	// 				width = elt_width;
	// 			}
	// 		}
	// 	}

	// 	Element::set_size({width, size.h});
	// }

	int added_sizes = 0;

	if (!direction) { // DIRECTION_H
		int available_width = this->size.w, expandable_elts = elements.size(), pad;

		for (auto& elt : elements) {
			if (!elt->get_expandable()) {
				available_width -= elt->get_width();
				expandable_elts--;
			}
		}

		if (expandable_elts != 0) {
			pad = available_width % expandable_elts;
			available_width /= expandable_elts;
		}

		for (auto& elt : elements) {
			elt->set_position({position.x + added_sizes, position.y});
			if (elt->get_expandable() && expandable) {
				if (expandable_elts == 1) {
					available_width += pad;
				}
				elt->set_size({available_width, size.h});
				expandable_elts--;
			} else {
				elt->set_height(size.h);
			}
			added_sizes += elt->get_width();
		}

	} else { // DIRECTION_V
		for (auto& elt : elements) {
			elt->set_position({position.x, position.y + added_sizes});
			elt->set_width(this->size.w);
			added_sizes += elt->get_height();
		}
	}
}

void Frame::set_direction(bool direction) {
	this->direction = direction;
}

void Frame::set_color_r(const COLOR& color) {
	set_color(color);
	for (auto& elt : elements) {
		// if ((elt) == (Frame))
		elt->set_color_r(color);
	}
}

void Frame::set_background_color_r(const COLOR& background_color) {
	set_background_color(background_color);
	for (auto& elt : elements) {
		elt->set_background_color_r(background_color);
	}
}

void Frame::show() const {
	Element::show();

	for (auto& elt : elements) {
		elt->show();
	}
}

const Element& Frame::get_elt(int index) const {
	if (index < 0 || index >= elements.size()) {
		throw out_of_range("Index out of range");
	}
	return *elements[index];
}
