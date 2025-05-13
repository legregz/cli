#pragma once

#include "element.hpp"
#include <memory>

template <typename Derived> class ClonableElement : public Element {
public:
	unique_ptr<Element> clone() const final override {
		return make_unique<Derived>(static_cast<const Derived&>(*this));
	}
};
