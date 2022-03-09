#include "Rectangle.h"


MyRectangle::MyRectangle(const Point& start_point, bool is_vertical):
	m_is_vertical(is_vertical)
{
	if(is_vertical)
	{
		Point p1(start_point);
		Point p2(start_point.get_x(), start_point.get_y() + 1, start_point.get_figure());
		Point p3(start_point.get_x(), start_point.get_y() + 2);
		Point p4(start_point.get_x(), start_point.get_y() + 3);

		m_points = {
			p1,
			p2,
			p3,
			p4
		};
	}
	else
	{
		Point p1(start_point.get_x() - 1, start_point.get_y(), start_point.get_figure());
		Point p2(start_point);
		Point p3(start_point.get_x() + 1, start_point.get_y(), start_point.get_figure());
		Point p4(start_point.get_x() + 2, start_point.get_y(), start_point.get_figure());

		m_points = {
			p1,
			p2,
			p3,
			p4
		};
	}
}

MyRectangle::MyRectangle(const std::array<Point, 4> points, bool is_vertical):
m_is_vertical(is_vertical)
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

std::unique_ptr<Shape> MyRectangle::fetch_move(Movement movement)
{
	Point point(m_points[0].get_x(), m_points[0].get_y());
	std::unique_ptr<MyRectangle> temp_shape = std::make_unique<MyRectangle>(m_points,m_is_vertical);
	temp_shape->move(movement);
	return std::move(temp_shape);
}

void MyRectangle::move(Movement movement)
{
	if ((Movement::Down == movement) ||
		(Movement::Left == movement) ||
		Movement::Right == movement)
	{
		for (auto& point : m_points)
		{
			point.move(movement);
		}
	}

	if(Movement::RotateClockwise == movement || 
		Movement::RotateCounterClockwise == movement)
	{
		_rotate();
		m_is_vertical = !m_is_vertical;
	}
}

void MyRectangle::_rotate()
{
	if(m_is_vertical)
	{
		MyRectangle temp_vertical(m_points[1], false);
		m_points = temp_vertical.get_points();
	}
	else
	{
		// Start drawing from second point..as in other games
		MyRectangle temp_vertical(m_points[1]);
		m_points = temp_vertical.get_points();
	}
}