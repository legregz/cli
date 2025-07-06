// #pragma once

// #include "component.hpp"
// #include <memory>

// template <typename Derived> class ClonableComponent : public Component {
// public:
// 	unique_ptr<Component> clone() const final override {
// 		return make_unique<Derived>(static_cast<const Derived&>(*this));
// 	}
// };
