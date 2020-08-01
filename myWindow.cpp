/*** myWindow.cpp start ***/

#include "myWindow.h"

MyWindow::MyWindow(unsigned int sizeX, unsigned int sizeY)
	: dr(), hBoxMaster(false, 30)
{
	set_title("Mass on table");
	set_default_size(sizeX, sizeY);
	set_border_width(10);

	/* add all the gtk stuff together */
	add(hBoxMaster);
	mainFrame.add(dr);
	hBoxMaster.pack_start(mainFrame);
	
	show_all_children();
}

MyWindow::~MyWindow(){
	timeout.disconnect();
}

void MyWindow::start(unsigned int miliSecondsDT){
	timeout = Glib::signal_timeout().connect( sigc::mem_fun(dr,
				&drawer::reCalculate), miliSecondsDT);
}


/*** myWindow.cpp end ***/
