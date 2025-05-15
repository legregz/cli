#pragma once

#include "element.hpp"
#include "style.h"

class AlignableElement : virtual public Element {
protected:
	ALIGNMENT alignment;

public:
	AlignableElement();

	const ALIGNMENT get_alignment() const;

	void set_alignment(const ALIGNMENT& alignment);

	void show(const SIZE element_minimal_size) const;
};
