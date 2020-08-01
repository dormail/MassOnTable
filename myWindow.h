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
		Gtk::Frame mainFrame;
		/* slot which provides a call every x second */
		sigc::connection timeout;

		/* gtk stuff */
		Gtk::HBox hBoxMaster;

	public:
		/* constructor and destructor */
		MyWindow(unsigned int sizeX, unsigned int sizeY);
		~MyWindow();
		
		/* @brief startx the calculating
		 *
		 * @param milisecondsDT time between each calculation step (the smaller the better
		 */
		void start(unsigned int miliSecondsDT);
};

		


#endif

/*** myWindow.h end ***/
