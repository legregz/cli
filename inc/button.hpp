#pragma once

#include "frame.hpp"

class Button : public Frame {
public:
	Button();

	Button(const Button& other);

	void show() const override;
};
