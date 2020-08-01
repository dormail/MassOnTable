/*** drawer.h start 
 * m1 = mass on the table
 * m2 = hanging mass
 * ***/

#ifndef DRAWER_H
#define DRAWER_H

#include <gtkmm.h>

class drawer : public Gtk::DrawingArea {
	protected:
		/* physical constants
		 * l = length of the rope connecting m1 and m2 
		 * g = gravitational acceleration
		 * m1, m2 masses
		 * */
		double l, g, m1, m2;
	
		/* generalised coordinates 
		 * p = phi (orientation from m1)
		 * r = radius (distance from m1 to the center of the table) */
		double p, r;
	
		/* values for numerical computation 
		 * w = omega (time-derivative of phi)
		 * v2 = \dot z (time derivative of z, speed of m2)
		 * a2 = \ddot z (second time derivative of z, speed of m2)
		 * L = angular momentum of m1 (which is constant)
		 * */
		double w, v1, v2, a1, a2, L;
	
		/* cartesian coordinates
		 * x,y for m1
		 * z for m2 */
		double x1, y1, z2;

		/* for checking time differences */
		std::chrono::system_clock::time_point lastTime;
	
		/* overwritten drawing method */
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	public:
		/* construct a new drawer */
		drawer();

		/* destroy the drawer object */
		virtual ~drawer();

		/* setter methods */
		void set_m1(double m);
		void set_m2(double m);
		void set_l(double l_new);
		void set_L(double L_new);
		void set_g(double g_new);

		/* recalculate for each physical frame
		 * @return true success */
		bool reCalculate();
};

#endif

/*** drawer.h end ***/
