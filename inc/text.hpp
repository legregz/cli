#pragma once

#include "clonableelement.hpp"

class Text : public ClonableElement<Text> {
private:
	char alignment;
	string text;
public:
	Text();

	const char get_alignment() const;
	const string& get_text() const;

	void set_alignment(char alignment);
	void set_text(const string& text);

	void show() const override;
};
