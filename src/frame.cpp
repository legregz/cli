#include "../inc/frame.hpp"

#include <memory>
#include <stdexcept>

// template class ClonableComponent<Frame>;

Frame::Frame() : direction(HORIZONTAL), components(vector<shared_ptr<Component>>()) {set_size({0, 0}); set_expandable({true, true});}

// Frame::Frame(const Frame& other) : ClonableComponent(other) {
// 	direction = other.direction;

// 	for (const auto& component : other.components) {
// 		components.push_back(component->clone());
// 	}
// }

bool Frame::get_direction() const {
	return direction;
}

void Frame::add(shared_ptr<Component> component) {
	components.push_back(component);
	if (!direction) {
		set_content_size({content_size.w + component->get_minimal_width(), content_size.h < component->get_minimal_height() ? component->get_minimal_height() : content_size.h});
	} else {
		set_content_size({content_size.w < component->get_minimal_width() ? component->get_minimal_width() : content_size.w, content_size.h + component->get_minimal_height()});
	}
}

void Frame::update_size() {
	int added_sizes = 0;

	if (!direction) { // HORIZONTAL
		int available_width = size.w, expandable_components = components.size(), pad;

		// determine the amount of horizontal expandable components and adapt the available width of the frame
		for (auto& component : components) {
			if (!component->get_expandable().w) {
				available_width -= component->get_minimal_width();
				expandable_components--;
			}
		}

		// determine the width of the horizontal expandable components
		if (expandable_components != 0) {
			pad = available_width % expandable_components;
			available_width /= expandable_components;
		} else {
			added_sizes = get_content_position().x - position.x;
		}

		for (auto& component : components) {
			if (component->get_expandable().w && expandable.w) {
				if (expandable_components == 1) {
					available_width += pad;
				}
				component->set_width(available_width);
				expandable_components--;
			} else {
				component->set_width(component->get_minimal_width());
			}

			if (component->get_expandable().h) {
				component->set_height(size.h);
			} else {
				component->set_height(component->get_minimal_height());
			}
			component->set_position({position.x + added_sizes, get_content_position(component->get_size()).y});
			component->update_size();
			added_sizes += component->get_width();
		}

	} else { // VERTICAL
		int available_height = size.h, expandable_components = components.size(), pad;

		// determine the amount of vertical expandable components and adapt the available height of the frame
		for (auto& component : components) {
			if (!component->get_expandable().h) {
				available_height -= component->get_minimal_height();
				expandable_components--;
			}
		}

		// determine the width of the horizontal expandable components
		if (expandable_components != 0) {
			pad = available_height % expandable_components;
			available_height /= expandable_components;
		} else {
			added_sizes = get_content_position().y - position.y;
		}

		for (auto& component : components) {
			if (component->get_expandable().h && expandable.h) {
				if (expandable_components == 1) {
					available_height += pad;
				}
				component->set_height(available_height);
				expandable_components--;
			} else {
				component->set_height(component->get_minimal_height());
			}

			if (component->get_expandable().w) {
				component->set_width(size.w);
			} else {
				component->set_width(component->get_minimal_width());
			}
			component->set_position({get_content_position(component->get_size()).x, position.y + added_sizes});
			component->update_size();
			added_sizes += component->get_height();
		}
	}
}

void Frame::set_direction(bool direction) {
	this->direction = direction;
}

void Frame::set_foreground_r(const COLOR& foreground) {
	set_foreground(foreground);
	for (auto& component : components) {
		// if (component == (Frame))
		component->set_foreground_r(foreground);
	}
}

void Frame::set_background_r(const COLOR& background) {
	set_background(background);
	for (auto& component : components) {
		component->set_background_r(background);
	}
}

void Frame::show() const {
	Component::show();

	for (auto& component : components) {
		component->show();
	}
}

const Component& Frame::get_component(int index) const {
	if (index < 0 || index >= components.size()) {
		throw out_of_range("Index out of range");
	}
	return *components[index];
}
