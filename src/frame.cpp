#include "../inc/frame.hpp"

#include <memory>
#include <stdexcept>

// template class ClonableElement<Frame>;

Frame::Frame() : direction(HORIZONTAL), elements(vector<shared_ptr<Element>>()) {set_size({0, 0}); set_expandable({true, true});}

// Frame::Frame(const Frame& other) : ClonableElement(other) {
// 	direction = other.direction;

// 	for (const auto& elt : other.elements) {
// 		elements.push_back(elt->clone());
// 	}
// }

bool Frame::get_direction() const {
	return direction;
}

void Frame::add(Element& elt) {
	elements.push_back((shared_ptr<Element>)&elt);
	if (!direction) {
		set_content_size({content_size.w + elt.get_minimal_width(), content_size.h < elt.get_minimal_height() ? elt.get_minimal_height() : content_size.h});
	} else {
		set_content_size({content_size.w < elt.get_minimal_width() ? elt.get_minimal_width() : content_size.w, content_size.h + elt.get_minimal_height()});
	}
}

void Frame::update_size() {
	int added_sizes = 0;

	if (!direction) { // HORIZONTAL
		int available_width = size.w, expandable_elts = elements.size(), pad;

		// determine the amount of horizontal expandable elements and adapt the available width of the frame
		for (auto& elt : elements) {
			if (!elt->get_expandable().w) {
				available_width -= elt->get_minimal_width();
				expandable_elts--;
			}
		}

		// determine the width of the horizontal expandable elements
		if (expandable_elts != 0) {
			pad = available_width % expandable_elts;
			available_width /= expandable_elts;
		} else {
			added_sizes = get_content_position().x - position.x;
		}

		for (auto& elt : elements) {
			if (elt->get_expandable().w && expandable.w) {
				if (expandable_elts == 1) {
					available_width += pad;
				}
				elt->set_width(available_width);
				expandable_elts--;
			} else {
				elt->set_width(elt->get_minimal_width());
			}

			if (elt->get_expandable().h) {
				elt->set_height(size.h);
			} else {
				elt->set_height(elt->get_minimal_height());
			}
			elt->set_position({position.x + added_sizes, get_content_position(elt->get_size()).y});
			elt->update_size();
			added_sizes += elt->get_width();
		}

	} else { // VERTICAL
		int available_height = size.h, expandable_elts = elements.size(), pad;

		// determine the amount of vertical expandable elements and adapt the available height of the frame
		for (auto& elt : elements) {
			if (!elt->get_expandable().h) {
				available_height -= elt->get_minimal_height();
				expandable_elts--;
			}
		}

		// determine the width of the horizontal expandable elements
		if (expandable_elts != 0) {
			pad = available_height % expandable_elts;
			available_height /= expandable_elts;
		} else {
			added_sizes = get_content_position().y - position.y;
		}

		for (auto& elt : elements) {
			if (elt->get_expandable().h && expandable.h) {
				if (expandable_elts == 1) {
					available_height += pad;
				}
				elt->set_height(available_height);
				expandable_elts--;
			} else {
				elt->set_height(elt->get_minimal_height());
			}

			if (elt->get_expandable().w) {
				elt->set_width(size.w);
			} else {
				elt->set_width(elt->get_minimal_width());
			}
			elt->set_position({get_content_position(elt->get_size()).x, position.y + added_sizes});
			elt->update_size();
			added_sizes += elt->get_height();
		}
	}
}

void Frame::set_direction(bool direction) {
	this->direction = direction;
}

void Frame::set_foreground_r(const COLOR& foreground) {
	set_foreground(foreground);
	for (auto& elt : elements) {
		// if ((elt) == (Frame))
		elt->set_foreground_r(foreground);
	}
}

void Frame::set_background_r(const COLOR& background) {
	set_background(background);
	for (auto& elt : elements) {
		elt->set_background_r(background);
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
