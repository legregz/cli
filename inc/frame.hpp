#pragma once

#include "clonableelement.hpp"
#include "element.hpp"
#include <vector>

class Frame : public ClonableElement<Frame> {
protected:
	bool direction;
	vector<unique_ptr<Element>> elements;
public:
	Frame();

	Frame(const Frame& other);

	bool get_direction() const;
	const Element& get_elt(int index) const;

	void set_direction(bool direction);
	virtual void set_color_r(const COLOR& color) override;
	virtual void set_background_color_r(const COLOR& background_color) override;
	void update_size() override;

	void add(Element& elt);
	void show() const override;
};
