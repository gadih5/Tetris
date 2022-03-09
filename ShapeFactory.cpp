#include "ShapeFactory.h"


std::unique_ptr<Shape> ShapeFactory::create_shape(const Point& start_point)
{
	int random_number = std::rand() % 7;
	
	switch (random_number)
	{
	case 0:
		return std::make_unique<Square>(start_point);
	case 1:
		return std::make_unique<MyRectangle>(start_point);

	case 2:
		return std::make_unique<LShape>(start_point);
		
	case 3:
		return std::make_unique<JShape>(start_point);
		
	case 4:
		return std::make_unique<TShape>(start_point);
		
	case 5:
		return std::make_unique<ZShape>(start_point);
	
	case 6:
		return std::make_unique<SShape>(start_point);
		
	default:
		return std::make_unique<Square>(start_point);

	}
}