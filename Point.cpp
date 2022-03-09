#include "Point.h"

void Point::draw() const {
	independent_gotoxy(m_x, m_y);
	std::cout << m_figure << std::endl;
}

bool Point::compare(const Point& point) const
{
	return ((point.get_x() == m_x) && (point.get_y() == m_y));
}

void Point::move(int direction) {
	switch (direction) {
	case 0: // UP
		m_y--;
	case 1: // DOWN
		m_y++;
		break;
	case 2: // LEFT
		m_x--;
		break;
	case 3: // RIGHT
		m_x++;
		break;
	}
}