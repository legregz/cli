#pragma once

#include "clonableelement.hpp"
#include "style.h"

class Text : public ClonableElement<Text> {
private:
	ALIGNMENT alignment;
	string text;
public:
	Text();

	const ALIGNMENT get_alignment() const;
	const string& get_text() const;

	void set_alignment(const ALIGNMENT& alignment);
	void set_text(const string& text);

	void show() const override;
};
