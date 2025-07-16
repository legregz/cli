#include "../inc/window.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

Window::Window() {set_expandable({true, true});}

void Window::update_size() {
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	Component::set_position(position);

	SIZE minimal_size = get_minimal_size();

	if (ws.ws_col < minimal_size.w || ws.ws_row < minimal_size.h) {
		correct_size = false;
		return;
	}

	correct_size = true;
	Frame::set_size({ws.ws_col, ws.ws_row});
	Frame::update_size();
}

void Window::show() const {
	if (!correct_size) {
		cout << "terminal size too tiny !" << endl;
		return;
	}

	system("clear");
	Frame::show();
}
