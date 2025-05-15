#pragma once

#include "alignableelement.hpp"
#include "clonableelement.hpp"
#include <vector>

class Image : public ClonableElement<Image>, public AlignableElement {
private:
	string path;
	vector<vector<CHAR>> image;
public:
	Image();

	const string& get_path() const;

	void set_path(const string& path);
	void set_dimensions(const array<int, 2>& dimensions);

	void show() const override;
};
