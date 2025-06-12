#pragma once

#include "element.hpp"
#include <memory>
#include <vector>

class Frame : public Element {
protected:
	bool direction;
	vector<shared_ptr<Element>> elements;
public:
	Frame();

	Frame(const Frame& other);

	bool get_direction() const;
	const Element& get_elt(int index) const;

	void set_direction(bool direction);
	virtual void set_foreground_r(const COLOR& foreground) override;
	virtual void set_background_r(const COLOR& background) override;
	void update_size() override;

	void add(Element& elt);
	void show() const override;
};
