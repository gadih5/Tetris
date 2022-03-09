#include "Square.h"

Square::Square(const Point& start_point)
{
	Point p1(start_point);
	Point p2(start_point.get_x()+1, start_point.get_y(), start_point.get_figure());
	Point p3(start_point.get_x(), start_point.get_y() + 1, start_point.get_figure());
	Point p4(start_point.get_x() + 1, start_point.get_y() +1, start_point.get_figure());
	
	m_points = {
		p1,
		p2,
		p3,
		p4
	};
}

Square::Square(const std::array<Point, 4> points)
{
	Point p1(points[0]);
	Point p2(points[1]);
	Point p3(points[2]);
	Point p4(points[3]);

	m_points = {
		p1,
		p2,
		p3,
		p4
	};
}


std::unique_ptr<Shape> Square::fetch_move(Movement movement)
{
	Point point(m_points[0].get_x(), m_points[0].get_y());
	std::unique_ptr<Square> temp_shape = std::make_unique<Square>(point);
	temp_shape->move(movement);
	return std::move(temp_shape);
}

void Square::move(Movement movement)
{
	// No rotate in shape
	if((Movement::Down == movement) ||
		(Movement::Left == movement) ||
		Movement::Right == movement)
	{
		for(auto& point : m_points)
		{
			point.move(movement);
		}
	}
}
