#pragma once
#include "Shape.h"


/* Class for 'S' shape
 *	---
 *	-##
 *	##-
 */

class SShape :
	public Shape
{
public:
	SShape(const Point& start_point) : SShape(start_point, true) {}

	SShape(const Point& start_point, bool is_vertical);
	SShape(const std::array<Point, 4> points, bool is_vertical);
	virtual ~SShape() = default;

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
	*				and moves the S-Shape according to this movement.
	*/
	void move(Movement move);
	/*
	* Function:  _rotate
	* ------------------
	* Description: This function rotates the S-Shape.
	*/
	void _rotate();

private:
	bool m_is_vertical;
};
