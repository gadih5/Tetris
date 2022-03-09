#pragma once
#include "Shape.h"


/* Class for 'L' shape:
 *	-#-
 *	-#-
 *	-##
 */

class LShape :
	public Shape
{
public:
	LShape(const Point& start_point);
	LShape(const Point& start_point, RotationStatus rotation_status);
	LShape(const std::array<Point, 4> points, RotationStatus state);
	virtual ~LShape() = default;

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
	 *				and moves the L-Shape according to this movement.
	 */
	void move(Movement move);
	/*
	* Function:  _rotate_clockwise
	* -----------------------------
	* Description: This function rotates the L-Shape in clockwise direction.
	*/
	void _rotate_clockwise();
	/*
	* Function:  _rotate_counter_clockwise
	* ------------------------------------
	* Description: This function rotates the L-Shape in counterclockwise direction.
	*/
	void _rotate_counter_clockwise();
private:
	RotationStatus m_rotation_status;

};
