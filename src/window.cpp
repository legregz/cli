#include "../inc/window.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

Window::Window() {}

void Window::set_size() {
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	Element::set_position(position);
	Frame::set_size({ws.ws_col, ws.ws_row});
}

void Window::show() const {
	system("clear");
	Frame::show();
}
