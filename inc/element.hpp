#pragma once

#include "style.h"
#include <memory>

class Element {
protected:
	COLOR foreground, background;
	EXPANDABLE expandable;
	SIZE size, content_size;
	POSITION position;
	BORDER border;
	PADDING padding;
	ALIGNMENT alignment;

	virtual void set_minimal_size(SIZE minimal_size);
	virtual void set_content_size(SIZE content_size);
public:
	Element();

	virtual COLOR get_foreground() const;
	virtual COLOR get_background() const;
	virtual EXPANDABLE get_expandable() const;
	virtual SIZE get_size() const;
	virtual int get_width() const;
	virtual int get_height() const;
	virtual SIZE get_minimal_size() const;
	virtual int get_minimal_width() const;
	virtual int get_minimal_height() const;
	virtual SIZE get_content_size() const;
	virtual int get_content_width() const;
	virtual int get_content_height() const;
	virtual POSITION get_position() const;
	virtual BORDER get_border() const;
	virtual PADDING get_padding() const;
	virtual ALIGNMENT get_alignment() const;
	virtual POSITION get_content_position() const;

	virtual void set_foreground(const COLOR& foreground);
	virtual void set_foreground_r(const COLOR& foreground);
	virtual void set_background(const COLOR& background);
	virtual void set_background_r(const COLOR& background);
	virtual void set_expandable(const EXPANDABLE& expandable);
	virtual void set_size(const SIZE& size);
	virtual void update_size();
	virtual void set_width(int width);
	virtual void set_height(int height);
	virtual void set_position(const POSITION& size);
	virtual void set_border(const BORDER& border);
	virtual void set_padding(const PADDING& padding);
	virtual void set_alignment(const ALIGNMENT& alignment);

	virtual unique_ptr<Element> clone() const = 0;

	virtual void show() const = 0;

	virtual ~Element() = default;
};
