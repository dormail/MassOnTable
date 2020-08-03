/*** drawer.cpp start ***/

#include "drawer.h"
#include <cmath>
#include <iostream>

drawer::drawer() : 
	l(5), g(9.81), m1(2), m2(2), p(0), r(2), L(10.0)
{
	lastTime = std::chrono::system_clock::now();
}

drawer::~drawer(){
}

bool drawer::reCalculate() {
	double dT = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now() - lastTime).count() / 1000.0;

	// approximate system every microsecond
	double physicalTime = 0.000001;

	while(dT > physicalTime) {
		/* calculate angular speed based on distance r */
		w = L / (m1 * r * r);
		p += w * physicalTime;

		/* calculate acceleration of m1 */
		a1 = (1 / (m1 + m2)) * (L * L / (m1 * r * r * r)) - (m2 / (m1 + m2)) * g;
		v1 += a1 * physicalTime;
		r += v1 * physicalTime;

		/* check if constraint of rope is fullfilled */
		if (r >= l) {
			r = l;
		}
		if (r <= 0) {
			r = 0.00001;
		}
		
		//a2 = (1 / (m1 + m2)) * (L * L / (m1 * r * r * r)) - (m2 / (m1 + m2)) * g;

		//v2 += a2 * physicalTime;
		//z2 += v2 * physicalTime;
		/* if m2 hangs further down than the rope or is at the tables height */
		//if (z2 > l) z2 = l;
		//if (z2 > 0) z2 = 0;

		dT -= physicalTime;
	}
	
	// catch up to real time pased
	if (dT != 0) {
		/* calculate angular speed based on distance r */
		w = L / (m1 * r * r);
		p += w * physicalTime;

		/* calculate acceleration of m2 */
		a2 = (1 / (m1 + m2)) * (L * L / (m1 * r * r * r)) - (m2 / (m1 + m2)) * g;
		v2 += a2 * physicalTime;
		z2 += v2 * physicalTime;
	}

	// draw
	queue_draw();

	lastTime = std::chrono::system_clock::now();

	return true;
}

bool drawer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	// getting size of the drawing area
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// x and y of the center
	int xc, yc;
	xc = width / 2;
	yc = width / 2;

	/* scaling according to window size */
	double scale = 1;
	if (width > height) 
		scale = yc / (2 * l);
	else 
		scale = xc / (2 * l);

	scale *= 0.95;

	/* since we are not looking directly on to the table we need to scale down the y-component */
	double viewingAngle = 0.75;

	// calculate position in cartesian space
	x1 = int(cos(p) * r * scale);
	y1 = int(sin(p) * r * scale * viewingAngle);
	z2 = int((r-l) * scale);

	/* draw m1 */
	cr->arc(xc+x1, yc+y1, 8, 0.0, 2.0 * M_PI);
	cr->set_source_rgb(0.0, 0.0, 0.8);
	cr->stroke();

	/* draw m2 */
	cr->arc(xc, yc-z2, 8, 0.0, 2.0 * M_PI);
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->stroke();

	/* draw line between center and m1 */
	cr->move_to(xc,yc);
	cr->line_to(xc+x1, yc+y1);
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->stroke();

	/* draw line between center and m2 */
	cr->move_to(xc,yc);
	cr->line_to(xc,yc - z2);
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->stroke();
	// std::cout = best debugger on planet earth
	//if (z2 < 0) std::cout << "z2 < 0\n";
	
	/* sending signal for energy display */
	signalEnergy.emit(energy());

	return true;
}

/* setter methods */
void drawer::set_m1(double m) {
	m1 = m;
}

void drawer::set_m2(double m) {
	m2 = m;
}

void drawer::set_l(double l_new) {
	l = l_new;
}

void drawer::set_L(double L_new) {
	L = L_new;
}

void drawer::set_g(double g_new) {
	g = g_new;
}

/* methods calculating energy in the system */
double drawer::T(){
	/* Tx = kinetic energy of mx */
	double T1 = 0.5 * m1 * (w * w * r * r + v1 * v1);
	double T2 = 0.5 * m2 * v2 * v2;
	return T1 + T2;
}

double drawer::V(){
	/* since we define E_pot = 0 at z = 0 m1 has not potential energy */
	return -1 * m2 * g * z2;
}

double drawer::energy(){
	/* E = T + V */
	return T() + V();
}

/*** drawer.cpp end ***/
