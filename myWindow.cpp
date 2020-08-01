/*** myWindow.cpp start ***/

#include "myWindow.h"

MyWindow::MyWindow(unsigned int sizeX, unsigned int sizeY)
	: dr(), 
	/* setting master boxes */
	hBoxMaster(false, 30),
	vBoxSettings(false, 10),
	/* setting small boxes for each setting */
	boxM1(false, 10),
	boxM2(false, 10),
	boxl(false, 10),
	boxL(false, 10),
	boxG(false, 10),
	/* setting buttons */
	buttonM1(Gtk::Adjustment::create(1, 0.001, 1000, 0.5, 1, 42), 0, 1),
	/* setting labels for the buttons */
	labelM1("Mass 1 = "),
	labelM2("Mass 2 = "),
	labell("l = "),
	labelL("L = "),
	labelG("g = "),
	/* setting units */
	unitM1("kg"),
	unitM2("kg"),
	unitlength("m"),
	unitG("m/s²"),
	unitL("kg m²/s")
{
	set_title("Mass on table");
	set_default_size(sizeX, sizeY);
	set_border_width(10);

	/* add all the gtk stuff together */
	/* Global HBox, Settings and Drawing area */
	add(hBoxMaster);
	mainFrame.add(dr);
	hBoxMaster.pack_start(mainFrame);
	hBoxMaster.pack_start(vBoxSettings, Gtk::PackOptions::PACK_SHRINK);

	/* adding settings to the setting VBox */
	/* m1 */
	boxM1.add(labelM1);
	boxM1.add(buttonM1);
	boxM1.add(unitM1);
	vBoxSettings.pack_start(boxM1, Gtk::PackOptions::PACK_SHRINK);
	/* m2 */
	boxM2.add(labelM2);
	boxM2.add(buttonM2);
	boxM2.add(unitM2);
	vBoxSettings.pack_start(boxM2, Gtk::PackOptions::PACK_SHRINK);

	/* L */
	boxL.add(labelL);
	boxL.add(buttonL);
	boxL.add(unitL);
	vBoxSettings.pack_start(boxL, Gtk::PackOptions::PACK_SHRINK);
	
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
