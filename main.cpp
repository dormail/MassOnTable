/*** main.cpp start ***/

#include <gtkmm.h>
#include "myWindow.h"

int main(int argc, char *argv[]){
	auto app = Gtk::Application::create(argc, argv,
			"org.gtkmm.examples.base");

	/* construct new window */
	MyWindow win(400, 400);

	/* ~60 repaints a second */
	win.start(17);

	return app->run(win);
}

/*** main.cpp end ***/
