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
	boxE(false, 10),
	/* setting buttons */
	buttonM1(Gtk::Adjustment::create(1, 0.001, 1000, 0.1, 1, 42), 0, 1),
	buttonM2(Gtk::Adjustment::create(1, 0.001, 1000, 0.1, 1, 42), 0, 1),
	buttonl(Gtk::Adjustment::create(5, 0.001, 1000, 0.1, 1, 42), 0, 1),
	buttonL(Gtk::Adjustment::create(2, 0.001, 1000, 0.1, 1, 42), 0, 1),
	buttonG(Gtk::Adjustment::create(9.81, 0.001, 1000, 0.1, 1, 42), 0, 1),
	/* setting labels for the buttons */
	labelM1("Mass 1 = "),
	labelM2("Mass 2 = "),
	labell("l = "),
	labelL("L = "),
	labelG("g = "),
	labelE("Energy: "),
	labelEnergyDisplay(""),
	/* setting units */
	unitM1("kg"),
	unitM2("kg"),
	unitlength("m"),
	unitG("m/s²"),
	unitL("kg m²/s"),
	unitE("J")
{
	set_title("Mass on table");
	set_default_size(sizeX, sizeY);
	set_border_width(10);

	/* signal connections for settings */
	buttonM1.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onM1Change));
	dr.set_m1(buttonM1.get_value());
	buttonM2.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onM2Change));
	dr.set_m2(buttonM2.get_value());
	buttonl.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onlChange));
	dr.set_l(buttonl.get_value());
	buttonL.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onLChange));
	dr.set_L(buttonL.get_value());
	buttonG.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onGChange));
	dr.set_g(buttonL.get_value());

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
	/* l */
	boxl.add(labell);
	boxl.add(buttonl);
	boxl.add(unitlength);
	vBoxSettings.pack_start(boxl, Gtk::PackOptions::PACK_SHRINK);
	/* L */
	boxL.add(labelL);
	boxL.add(buttonL);
	boxL.add(unitL);
	vBoxSettings.pack_start(boxL, Gtk::PackOptions::PACK_SHRINK);
	/* g */
	boxG.add(labelG);
	boxG.add(buttonG);
	boxG.add(unitG);
	vBoxSettings.pack_start(boxG, Gtk::PackOptions::PACK_SHRINK);
	/* E */
	boxE.add(labelE);
	boxE.add(labelEnergyDisplay);
	boxE.add(unitE);
	vBoxSettings.pack_start(boxE, Gtk::PackOptions::PACK_SHRINK);
	/* connect E label to E signal from the drawer */
	dr.signalEnergy.connect(sigc::mem_fun1(this, &MyWindow::setTotalEnergyLabel));
	
	show_all_children();
}

MyWindow::~MyWindow(){
	timeout.disconnect();
}

void MyWindow::start(unsigned int miliSecondsDT){
	timeout = Glib::signal_timeout().connect( sigc::mem_fun(dr,
				&drawer::reCalculate), miliSecondsDT);
}

/* mothods when there is user input */
void MyWindow::onM1Change(){
	dr.set_m1(buttonM1.get_value());
}

void MyWindow::onM2Change(){
	dr.set_m2(buttonM2.get_value());
}

void MyWindow::onlChange(){
	dr.set_l(buttonl.get_value());
}

void MyWindow::onLChange(){
	dr.set_L(buttonL.get_value());
}

void MyWindow::onGChange(){
	dr.set_g(buttonG.get_value());
}

/* method setting energy label */
void MyWindow::setTotalEnergyLabel(double energy){
	labelEnergyDisplay.set_markup(Glib::ustring("<tt>").append(std::to_string(energy)).append("</tt>"));
	labelEnergyDisplay.set_width_chars(10);
}


/*** myWindow.cpp end ***/
