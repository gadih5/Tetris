#pragma once
#include "Shape.h"

/* Class For rectangle shape:
 *	-#-
 *	-#-
 *	-#-
 *	-#-
 */

// Class name is MyRectangle because Rectangle is already taken..
class MyRectangle : public Shape
{
public:
	MyRectangle(const Point& start_point): MyRectangle(start_point, true){}
	MyRectangle(const Point& start_point, bool horizinal);
	MyRectangle(const std::array<Point, 4> points, bool is_vertical);
	virtual ~MyRectangle() = default;

	/*
	* Function:  fetch_move
	* ----------------
	* Description: This function receives a movement (Down,Left,Right,RotateClockwise,RotateCounterClockwise)
	*				and return new moved shape (and its coordinates, according to the move)
	*/
	std::unique_ptr<Shape> fetch_move(Movement movement);
/*
* Function:  move
* ----------------
* Description: This function receives a movement (Down,Left,Right,RotateClockwise,RotateCounterClockwise)
*				and moves the Rectangle-Shape according to this movement.
*/
	void move(Movement move);
 /*
 * Function:  _rotate
 * --------------------
 * Description: This function rotates the Rectangle-Shape.
 */
	void _rotate();

private:
	bool m_is_vertical;
};
