#pragma once
#include "Shape.h"

/* Class for Square shape:
 *	##
 *	##
 */


class Square : public Shape
{
public:
	Square(const Point& start_point);
	Square(const std::array<Point, 4> points);
	virtual ~Square() = default;

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
	* Description: This function receives a movement (Down,Left,Right)
	*				and moves the Square-Shape according to this movement.
	*/
	void move(Movement move);
};
