#pragma once

#include "frame.hpp"

class Window : public Frame {
private:
	bool correct_size = true;

public:
	Window();

	// void init();
	void update_size() override;
	void show() const override;
};
