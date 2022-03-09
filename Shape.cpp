#include "Shape.h"

bool Shape::compare(const std::array<Point, 4>& array) const
{
	size_t i = 0;
	for(const auto& point : m_points)
	{
		if(!point.compare(array[i]))
		{
			return false;
		};
		i++;
	}
	return true;
}