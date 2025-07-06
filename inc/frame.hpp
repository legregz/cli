#pragma once

#include "component.hpp"
#include <memory>
#include <vector>

class Frame : public Component {
protected:
	bool direction;
	vector<shared_ptr<Component>> components;
public:
	Frame();

	// Frame(const Frame& other);

	bool get_direction() const;
	const Component& get_component(int index) const;

	void set_direction(bool direction);
	virtual void set_foreground_r(const COLOR& foreground) override;
	virtual void set_background_r(const COLOR& background) override;
	void update_size() override;

	void add(shared_ptr<Component> component);
	void show() const override;
};
