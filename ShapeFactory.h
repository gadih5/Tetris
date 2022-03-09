#pragma once

#include <memory>

#include "Shape.h"
#include "Square.h"
#include "Rectangle.h"
#include "LShape.h"
#include "JShape.h"
#include "TShape.h"
#include "ZShape.h"
#include "SShape.h"


// Factory class
class ShapeFactory
{
public:
	// Factory Method
	 /*
	 * Function:  create_shape
	 * -----------------------
	 * Description: This function receives a starting point
	 *              and produces one random Tetris shape out of seven.
	 *
	 *  return value: Shape
	 */
	static std::unique_ptr<Shape> create_shape(const Point& start_point);
};
