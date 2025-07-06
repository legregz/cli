#pragma once

#include "component.hpp"

class Text : public Component {
private:
	string text, style;
public:
	Text();

	const string& get_text() const;

	void set_text(const string& text);

	void show() const override;
};
