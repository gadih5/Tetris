#pragma once
#include "Shape.h"

/* Class for 'Z' Shape:
 *	---
 *	##-
 *	-##
 */

class ZShape :
	public Shape
{
public:
	ZShape(const Point& start_point) : ZShape(start_point, true) {}
	ZShape(const Point& start_point, bool is_vertical);
	ZShape(const std::array<Point, 4> points, bool is_vertical);
	virtual ~ZShape() = default;

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
	*				and moves the Z-Shape according to this movement.
	*/
	void move(Movement move);
	/*
	* Function:  _rotate
	* -------------------
	* Description: This function rotates the Z-Shape.
	*/
	void _rotate();

private:
	bool m_is_vertical;
};
