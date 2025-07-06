#pragma once

#include "frame.hpp"
#include "focusablecomponent.hpp"

class Button : public Frame, FocusableComponent {
public:
	Button();

	// Button(const Button& other);

	void show() const override;
};
