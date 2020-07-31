/*** myWindow.h start ***/

#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "drawer.h"
#include <chrono>
#include <cmath>
#include <gtkmm.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <boost/log/trivial.hpp>

// main window
class MyWindow : public Gtk::Window {
	protected:
		/* stuff realted to drawing */
		drawer dr;
		Gtk::Frame drawArea;
		/* slot which provides a call every x second */
		sigc::connection timeout;

		


#endif

/*** myWindow.h end ***/
