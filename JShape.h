#pragma once
#include "Shape.h"


/* Class for 'J' Shape:
 *	-#-
 *	-#-
 *	##-
 */

class JShape :
	public Shape
{
public:
	JShape(const Point& start_point);
	JShape(const Point& start_point, RotationStatus rotation_status);
	JShape(const std::array<Point, 4> points, RotationStatus state);
	virtual ~JShape() = default;


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
	*				and moves the J-Shape according to this movement.
	*/
	void move(Movement move);
	/*
	* Function:  _rotate_clockwise
	* -----------------------------
	* Description: This function rotates the J-Shape in clockwise direction.
	*/
	void _rotate_clockwise();
	/*
	* Function:  _rotate_counter_clockwise
	* ------------------------------------
	* Description: This function rotates the J-Shape in counterclockwise direction.
	*/
	void _rotate_counter_clockwise();

private:
	RotationStatus m_rotation_status;
};
