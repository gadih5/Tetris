#pragma once
#include <array>

#include "Point.h"

enum RotationStatus : int
{
	FirstState = 1,
	RotetedRight = 2,
	Inverted = 3,
	RotatedLeft = 4
};

/*
 *	Abstract Class for Tetris Shapes.
 *	Notice: Rectangle, ZShape & SShape has two ctor's which is being relative to the second point (other point are calculated according to it)
 *			LShape, JShape & TShape are being rotated 3 times, and can appear on board in a 4 different ways. Every rotate is being calculated according to all points.
 */

class Shape
{
public:

	std::unique_ptr<Shape> virtual fetch_move(Movement movement) = 0;

	virtual void move(Movement move) = 0;

	const std::array<Point,4>& get_points() { return m_points; }
	bool compare(const std::array<Point, 4>& array) const;

protected:
	std::array<Point, 4> m_points = {}; // All shapes contain 4 points.
};

