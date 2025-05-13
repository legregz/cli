#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "../inc/elements.hpp"
#include "../inc/functions.h"
#include "../inc/style.h"

Element::Element() : color(white), background_color(black), expandable(EXPANDABLE), size{0, 1}, position{1, 1}, border{0, 0, 0, 0} {}

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
	return {size.w + border.l + border.r, size.h + border.t + border.b};
}

int Element::get_width() const {
	return size.w + border.l + border.r;
}

int Element::get_height() const {
	return size.h + border.t + border.b;
}

POSITION Element::get_position() const {
	return {position.x - border.l, position.y - border.t};
}

BORDER Element::get_border() const {
	return border;
}

void Element::set_color(COLOR color) {
	this->color = color;
}

void Element::set_background_color(COLOR color) {
	this->background_color = color;
}

void Element::set_expandable(bool expandable) {
	this->expandable = expandable;
}

void Element::set_size(const SIZE& size) {
	this->size = {size.w - border.l - border.r, size.h - border.t - border.b};
	update_size();
}

void Element::update_size() {}

void Element::set_width(int width) {
	size.w = width - border.l - border.r;
	update_size();
}

void Element::set_height(int height) {
	size.h = height - border.t - border.b;
	update_size();
}

void Element::set_position(const POSITION& position) {
	this->position = {position.x + border.l, position.y + border.t};
}

void Element::set_border(const BORDER& border) {
	this->border = border;
}

template <typename Derived>
unique_ptr<Element> ClonableElement<Derived>::clone() const {
	return make_unique<Derived>(static_cast<const Derived&>(*this));
}

void Element::show() const {
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

	// cout << "\e[38;2;" << (int)color.r << ";" << (int)color.g << ";" << (int)color.b << 'm'<< "\e[48;2;" << (int)background_color.r << ";" << (int)background_color.g << ";" << (int)background_color.b << 'm';
}

Frame::Frame() : direction(DIRECTION_H) {Element::set_size({0, 0});}

Frame::Frame(const Frame& other) {
	color = other.color;
	background_color = other.background_color;
	expandable = other.expandable;
	size = other.size;
	border = other.border;
	direction = other.direction;

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

void Frame::show() const {
	// for (int y = 0; y < size.h; y++) {
	// 	cout << "\e[" << position.y + y << ";" << position.x << 'f';
	// 	spaces(size.w);
	// }

	Element::show();

	for (auto& elt : elements) {
		elt->show();
	}
}

Element& Frame::get_elt(int index) const {
	if (index < 0 || index >= elements.size()) {
		throw out_of_range("Index out of range");
	}
	return *elements[index];
}

// void Window::init() {
// 	// struct winsize ws;
// 	// ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
// 	// array<int, 2> s = {ws.ws_col, ws.ws_row};
// 	// set_size(s);
// 	printf("\033[s");
// }

Window::Window() {}

void Window::set_size() {
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	Element::set_position(position);
	Frame::set_size({ws.ws_col, ws.ws_row});
}

void Window::show() {
	system("clear");
	Frame::show();
}

Text::Text() : alignment('l') {}//set_expandable(H_EXPANDABLE);}

const char Text::get_alignment() const {
	return alignment;
}

const string& Text::get_text() const {
	return text;
}

void Text::set_alignment(char alignment) {
	this->alignment = alignment;
}

void Text::set_text(const string& text) {
	this->text = text;
	size.w = text.size();
}

void Text::show() const {
	Element::show();
	cout << "\e[" << position.y + size.h / 2 << ";" << position.x << 'f';

	double nb_spaces;
	switch (alignment) {
		case 'l':
			printl(text, size.w);
			spaces(size.w - text.size());
			break;
		case 'c':
			nb_spaces = (size.w - text.size()) / 2.0;
			spaces(nb_spaces + (nb_spaces - (int)nb_spaces > 0 ? 1 : 0));
			printl(text, size.w);
			spaces(nb_spaces);
			break;
		case 'r':
			spaces(size.w - text.size());
			printl(text, size.w);
			break;
	}
	cout << normal;
}

Image::Image() {set_expandable(NOT_EXPANDABLE);}

const string& Image::get_path() const {
	return path;
}

void Image::set_path(const string& path) {
	this->path = path;
}

void Image::set_dimensions(const array<int, 2>& dimensions) {
	Element::set_size({dimensions[0], dimensions[1] / 2});

	cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
	cv::Vec3b f_pixel, b_pixel;
	array<int, 3> avg_f_pixel, avg_b_pixel;
	int y_factor = img.rows / dimensions[1], x_factor = img.cols / dimensions[0], pixel_group_size = x_factor * y_factor;

	// if (img.empty()) {
	// 	std::cerr << "Erreur : Impossible de charger l'image!" << std::endl;
	// }

	image.resize(dimensions[1] / 2);

	for (int y = 0; y < dimensions[1]; y += 2) {
		for (int x = 0; x < dimensions[0]; x++) {
			avg_f_pixel = {0, 0, 0};
			avg_b_pixel = {0, 0, 0};

			for (int i = 0; i < x_factor; i++) {
				for (int j = 0; j < y_factor; j++) {
					f_pixel = img.at<cv::Vec3b>(y * y_factor, x * x_factor);
					b_pixel = img.at<cv::Vec3b>((y + 1) * y_factor, x * x_factor);

					for (int k = 0; k < 3; k++) {
						avg_f_pixel[k] += f_pixel[k];
						avg_b_pixel[k] += b_pixel[k];
					}
				}
			}

			for (int k = 0; k < 3; k++) {
				avg_f_pixel[k] /= pixel_group_size;
				avg_b_pixel[k] /= pixel_group_size;
			}

			image[y / 2].push_back({{(uint8_t)avg_f_pixel[2], (uint8_t)avg_f_pixel[1], (uint8_t)avg_f_pixel[0]}, {(uint8_t)avg_b_pixel[2], (uint8_t)avg_b_pixel[1], (uint8_t)avg_b_pixel[0]}});
		}
	}
}

void Image::show() const {
	COLOR f_color;
	COLOR b_color;

	for (int y = 0; y < image.size(); y++) {
		cout << "\e[" << position.y + y << ";" << position.x << 'f';
		for (int x = 0; x < image[y].size(); x++) {
			f_color = image[y][x].f_color;
			b_color = image[y][x].b_color;
			cout << "\e[38;2;" << (int)f_color.r << ";" << (int)f_color.g << ";" << (int)f_color.b << 'm' << "\e[48;2;" << (int)b_color.r << ";" << (int)b_color.g << ";" << (int)b_color.b << 'm' << "▀";
		}
	}
	cout << normal;
}

Button::Button() : Frame() {}

Button::Button(const Button& other) : Frame(other) {}

void Button::show() const {
	Frame::show();
}
