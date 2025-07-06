#pragma once

#include "component.hpp"
#include <vector>

class Image : public Component {
private:
	string path;
	vector<vector<CHAR>> image;
public:
	Image();

	const string& get_path() const;

	void set_path(const string& path);
	void set_dimensions(const SIZE& dimensions);

	void show() const override;
};
