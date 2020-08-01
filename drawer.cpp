/*** drawer.cpp start ***/

#include "drawer.h"
#include <cmath>

drawer::drawer() : 
	l(3), g(9.81), m1(1), m2(2), p(0), r(3), L(1)
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

		/* calculate acceleration of m2 */
		a2 = (1 / (m1 + m2)) * (L * L / (m1 * r * r * r)) - (m2 / (m1 + m2)) * g;
		v2 += a2 * physicalTime;
		z2 += v2 * physicalTime;

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

	/* todo: automatic scaling */
	double scale = 1;

	/* since we are not looking directly on to the table we need to scale down the y-component */
	double viewingAngle = 0.75;

	// calculate position in cartesian space
	x1 = int(cos(p) * r * scale);
	y1 = int(sin(p) * r * scale * viewingAngle);
	z2 = int(r-l);

	/* draw m1 */
	cr->arc(xc+x1, yc+y1, 4, 0.0, 2.0 * M_PI);
	cr->set_source_rgb(0.0, 0.0, 0.8);
	cr->stroke();

	/* draw m2 */
	cr->arc(xc, yc+z2, 4, 0.0, 2.0 * M_PI);
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->stroke();

	/* draw line between center and m1 */
	cr->move_to(xc,yc);
	cr->line_to(x1,y1);
	cr->stroke();

	/* draw line between center and m2 */
	cr->move_to(xc,yc);
	cr->line_to(0,z2);
	cr->stroke();

	return true;
}

/*** drawer.cpp end ***/
