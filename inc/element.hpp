#pragma once

#include "style.h"
#include <memory>

class Element {
protected:
	COLOR color;
	COLOR background_color;
	bool expandable;
	SIZE size;
	POSITION position;
	BORDER border;
	PADDING padding;
public:
	Element();

	virtual COLOR get_color() const;
	virtual COLOR get_background_color() const;
	virtual bool get_expandable() const;
	virtual SIZE get_size() const;
	virtual int get_width() const;
	virtual int get_height() const;
	virtual POSITION get_position() const;
	virtual BORDER get_border() const;
	virtual PADDING get_padding() const;

	virtual void set_color(const COLOR& color);
	virtual void set_background_color(const COLOR& background_color);
	virtual void set_expandable(bool expandable);
	virtual void set_size(const SIZE& size);
	virtual void update_size();
	virtual void set_width(int width);
	virtual void set_height(int height);
	virtual void set_position(const POSITION& size);
	virtual void set_border(const BORDER& border);
	virtual void set_padding(const PADDING& padding);

	virtual unique_ptr<Element> clone() const = 0;

	virtual void show() const = 0;

	virtual ~Element() = default;
};
