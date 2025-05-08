
#include <sys/ioctl.h>
#include <unistd.h>
#include "../inc/style.h"
#include "../inc/cli.h"

using namespace std;

int main() {
	// Window window;
	// window.init();
	// window.set_color(back_white);
	// window.set_direction(DIRECTION_V);

	Text title;
	title.set_text("salut");
	title.set_alignment('c');
	title.set_color(back_blue);

	Text add_button;
	add_button.set_text("+");
	add_button.set_color(back_green);
	add_button.set_expandable(NOT_EXPANDABLE);

	Text close_button;
	close_button.set_text("*");
	close_button.set_color(back_red);
	close_button.set_expandable(NOT_EXPANDABLE);

	// Text content;
	// content.set_text("bonjour les gens");
	// content.set_alignment('c');
	// content.set_color(back_violet);

	Frame header_Div;
	// header_Div.set_direction('v');
	header_Div.set_color(back_cyan);
	// header_Div.set_expandable(NOT_EXPANDABLE);

	Frame content_Div;
	content_Div.set_direction(DIRECTION_V);
	// content_Div.set_color(back_yellow);

	// Frame container_Div;
	// container_Div.set_direction(DIRECTION_H);
	// container_Div.set_expandable(NOT_EXPANDABLE);

	Window window;
	Image image;
	image.set_path("./assets/images/folder-developpement.png");
	image.set_dimensions({64, 64});
	window.add(image);

	// header_Div.add(add_button);
	// header_Div.add(title);
	// header_Div.add(close_button);
	// window.add(header_Div);
	// content_Div.add(image);
	// content_Div.add(header_Div);
	// content_Div.add(content);
	// container_Div.add(content_Div);
	// container_Div.add(content_Div);

	// map<string, shared_ptr<Element>> elements = open_elts_file("test");
	// content_Div.add(elements["error"]);

	window.show();

	return 0;
}
