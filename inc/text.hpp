#pragma once

#include "alignableelement.hpp"
#include "clonableelement.hpp"

class Text : public ClonableElement<Text>, public AlignableElement {
private:
	string text, style;
public:
	Text();

	const string& get_text() const;

	void set_text(const string& text);

	void show() const override;
};
