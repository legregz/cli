#pragma once

#include "element.hpp"

class Text : public Element {
private:
	string text, style;
public:
	Text();

	const string& get_text() const;

	void set_text(const string& text);

	void show() const override;
};
