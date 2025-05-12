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

const array<int, 2>& Element::get_size() const {
	return size;
}

const array<int, 2>& Element::get_position() const {
	return position;
}

const array<bool, 4>& Element::get_border() const {
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

void Element::set_size(const array<int, 2>& size) {
	this->size = size;
}

void Element::set_position(const array<int, 2>& position) {
	this->position = position;
}

void Element::set_border(const array<bool, 4>& border) {
	size[0] += border[0] - this->border[0] + border[2] - this->border[2];
	size[1] += border[1] - this->border[1] + border[3] - this->border[3];

	this->border = border;
}

template <typename Derived>
unique_ptr<Element> ClonableElement<Derived>::clone() const {
	return make_unique<Derived>(static_cast<const Derived&>(*this));
}

void Element::show() const {
	if (border[0]) {
		if (border[1]) {
			cout << "\e[" << position[1] << ";" << position[0] << "f┌";
		}
		for (int y = 0; y < size[1] - border[1] - border[3]; y++) {
			cout << "\e[" << position[1] + border[1] + y << ";" << position[0] << "f│";
		}
		if (border[3]) {
			cout << "\e[" << position[1] + size[1] - 1 << ";" << position[0] << "f└";
		}
	}
	if (border[2]) {
		if (border[1]) {
			cout << "\e[" << position[1] << ";" << position[0] + size[0] - 1 << "f┐";
		}
		for (int y = 0; y < size[1] - border[1] - border[3]; y++) {
			cout << "\e[" << position[1] + border[1] + y << ";" << position[0] + size[0] - 1 << "f│";
		}
		if (border[3]) {
			cout << "\e[" << position[1] + size[1] - 1 << ";" << position[0] + size[0] - 1 << "f┘";
		}
	}
	if (border[1]) {
		for (int x = 0; x < size[0] - border[0] - border[2]; x++) {
			cout << "\e[" << position[1] << ";" << position[0] + border[0] + x << "f─";
		}
	}
	if (border[3]) {
		for (int x = 0; x < size[0] - border[0] - border[2]; x++) {
			cout << "\e[" << position[1] + size[1] - 1 << ";" << position[0] + border[0] + x << "f─";
		}
	}

	// cout << "\e[38;2;" << (int)color.r << ";" << (int)color.g << ";" << (int)color.b << 'm'<< "\e[48;2;" << (int)background_color.r << ";" << (int)background_color.g << ";" << (int)background_color.b << 'm';
}

Frame::Frame() : direction(DIRECTION_H) {Element::set_size({0, 0});}

Frame::Frame(const Frame& other) {
	expandable = other.expandable;
	direction = other.direction;
	Element::set_size(other.get_size());
	color = other.color;

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
		Element::set_size({size[0] + elt.get_size()[0], size[1] < elt.get_size()[1] ? elt.get_size()[1] : size[1]});
	} else {
		Element::set_size({size[0] < elt.get_size()[0] ? elt.get_size()[0] : size[0], size[1] + elt.get_size()[1]});
	}
}

void Frame::set_size(const array<int, 2>& size) {
	// cout << "exp" << expandable << endl;

	if (expandable) {
		Element::set_size(size);
	} // else if (size[0] < this->size[0]) {
	// 	Element::set_size({size[0], this->size[1]});
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

	// 	Element::set_size({width, size[1]});
	// }

	int added_sizes = 0;

	if (!direction) { // DIRECTION_H
		int available_width = this->size[0], expandable_elts = elements.size(), pad;

		for (auto& elt : elements) {
			if (!elt->get_expandable()) {
				available_width -= elt->get_size()[0];
				expandable_elts--;
			}
		}

		if (expandable_elts != 0) {
			pad = available_width % expandable_elts;
			available_width /= expandable_elts;
		}

		for (auto& elt : elements) {
			elt->set_position({position[0] + added_sizes, position[1]});
			if (elt->get_expandable() && expandable) {
				if (expandable_elts == 1) {
					available_width += pad;
				}
				elt->set_size({available_width, size[1]});
				expandable_elts--;
			} else {
				elt->set_size(elt->get_size());
			}
			added_sizes += elt->get_size()[0];
		}

	} else { // DIRECTION_V
		for (auto& elt : elements) {
			elt->set_position({position[0], position[1] + added_sizes});
			elt->set_size({size[0], elt->get_size()[1]});
			added_sizes += elt->get_size()[1];
		}
	}
}

void Frame::set_direction(bool direction) {
	this->direction = direction;
}

void Frame::show() const {
	// for (int y = 0; y < size[1]; y++) {
	// 	cout << "\e[" << position[1] + y << ";" << position[0] << 'f';
	// 	spaces(size[0]);
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
	size[0] = text.size();
}

void Text::show() const {
	Element::show();
	cout << "\e[" << position[1] << ";" << position[0] << 'f';

	double nb_spaces;
	switch (alignment) {
		case 'l':
			printl(text, size[0]);
			spaces(size[0] - text.size());
			break;
		case 'c':
			nb_spaces = (size[0] - text.size()) / 2.0;
			spaces(nb_spaces + (nb_spaces - (int)nb_spaces > 0 ? 1 : 0));
			printl(text, size[0]);
			spaces(nb_spaces);
			break;
		case 'r':
			spaces(size[0] - text.size());
			printl(text, size[0]);
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
		cout << "\e[" << position[1] + y << ";" << position[0] << 'f';
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
