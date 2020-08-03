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
		// HBox containing everything
		Gtk::HBox hBoxMaster;
		// VBox with all the settings
		Gtk::VBox vBoxSettings;
		// HBox for each setting
		Gtk::HBox boxM1, boxM2, boxl, boxL, boxG, boxE;
		/* spin button for typing in values for m1, etc.
		 * Labels so that user knows what he is typing in
		 * Alignment for looks
		 * Energery box giving out energy
		 */
		Gtk::SpinButton buttonM1, buttonM2, buttonl, buttonL, buttonG;
		Gtk::Label labelM1, labelM2, labell, labelL, labelG, labelE;
		Gtk::Label unitM1, unitM2, unitlength, unitG, unitL, unitE;
		Gtk::Alignment buttonAlign;
		Gtk::Label totalEnergy, labelEnergyDisplay;

	public:
		/* constructor and destructor */
		MyWindow(unsigned int sizeX, unsigned int sizeY);
		~MyWindow();
		
		/* @brief startx the calculating
		 *
		 * @param milisecondsDT time between each calculation step (the smaller the better
		 */
		void start(unsigned int miliSecondsDT);

		/* methods when there is user input */
		void onM1Change();
		void onM2Change();
		void onlChange();
		void onLChange();
		void onGChange();

		/* Method setting the Energy value */
		void setTotalEnergyLabel(double Energy);
};

		


#endif

/*** myWindow.h end ***/
