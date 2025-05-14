#include "../inc/button.hpp"

Button::Button() : Frame() {}

Button::Button(const Button& other) : Frame(other) {}

void Button::show() const {
	Frame::show();
}
