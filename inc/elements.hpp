#include "style.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Element {
protected:
	COLOR color;
	COLOR background_color;
	bool expandable;
	SIZE size;
	POSITION position;
	BORDER border;
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

	virtual void set_color(COLOR color);
	virtual void set_background_color(COLOR background_color);
	virtual void set_expandable(bool expandable);
	virtual void set_size(const SIZE& size);
	virtual void update_size();
	virtual void set_width(int width);
	virtual void set_height(int height);
	virtual void set_position(const POSITION& size);
	virtual void set_border(const BORDER& border);

	virtual unique_ptr<Element> clone() const = 0;

	virtual void show() const = 0;

	virtual ~Element() = default;
};

template <typename Derived>
class ClonableElement : public Element {
	unique_ptr<Element> clone() const final override;
};

class Frame : public ClonableElement<Frame> {
protected:
	bool direction;
	vector<unique_ptr<Element>> elements;
public:
	Frame();

	Frame(const Frame& other);

	bool get_direction() const;
	Element& get_elt(int index) const;

	void set_direction(bool direction);
	void update_size() override;

	void add(Element& elt);
	void show() const override;
};

class Window : public Frame {
public:
	Window();

	// void init();
	void set_size();
	void show();
};

class Text : public ClonableElement<Text> {
private:
	char alignment;
	string text;
public:
	Text();

	const char get_alignment() const;
	const string& get_text() const;

	void set_alignment(char alignment);
	void set_text(const string& text);

	void show() const override;
};

class Image : public ClonableElement<Image> {
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

class Button : Frame {
public:
	Button();

	Button(const Button& other);

	void show() const override;
};
