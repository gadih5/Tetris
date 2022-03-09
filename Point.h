#pragma once

#include "UtilsIo.h"
#include "Helpers.h"

class Point {
public:

	Point(int x = 1, int y = 1, char figuare = ' ') :
		m_x(x),
		m_y(y),
		m_figure(figuare)
	{}
	Point(const Point& p) :
		m_x(p.get_x()),
		m_y(p.get_y()),
		m_figure(p.get_figure())
	{}

 /*
 * Function:  draw
 * ----------------
 * Description: This function draws a point on the board game according to the point's coordinates.
 */
	void draw() const;
	bool compare(const Point& point) const;
 /*
 * Function:  move
 * ----------------
 * Description: This function receives a direction (UP,DOWN,LEFT,RIGHT)
 *				and moves the point according to this direction.
 */
	void move(int direction);
 /*
 * Function:  get_x
 * ----------------
 * Description: This function returns the point's X value.
 */
	int get_x() const { return m_x; }
 /*
 * Function:  get_y
 * ----------------
 * Description: This function returns the point's Y value.
 */
	int get_y() const { return m_y; }
 /*
 * Function:  set_x
 * ----------------
 * Description: This function receives a numeric value
 *				and sets the point's X to this value.
 */
	void set_x(int x) { m_x = x; }
 /*
 * Function:  set_y
 * ----------------
 * Description: This function receives a numeric value
 *				and sets the point's Y to this value.
 */
	void set_y(int y) { m_y = y; }

/*
* Function:  get_figure
* ----------------
* Description: This function returns the point's figure value (character).
*/
	char get_figure() const { return m_figure;}
/*
* Function:  set_figure
* ----------------
* Description: This function receives a character
*			   and sets the point's figure to this character.
*/
	void set_figure(char figure) { m_figure = figure; }
private:
	int m_x;
	int m_y;
	char m_figure;
};