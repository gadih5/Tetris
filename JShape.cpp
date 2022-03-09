#include "JShape.h"

JShape::JShape(const Point& start_point) :
	m_rotation_status(RotationStatus::FirstState)
{
	/* FirstState is:
	 * -#-
	 * -#-
	 * ##-
	*/
	Point p1(start_point);
	Point p2(start_point.get_x(), start_point.get_y() + 1, start_point.get_figure());
	Point p3(start_point.get_x(), start_point.get_y() + 2);
	Point p4(start_point.get_x() -1, start_point.get_y() + 2);

	m_points = {
		p1,
		p2,
		p3,
		p4
	};
}

JShape::JShape(const std::array<Point,4> points, RotationStatus state):
	m_rotation_status(state)
{
	m_points = {
	points[0],
	points[1],
	points[2],
	points[3]
	};
}

std::unique_ptr<Shape> JShape::fetch_move(Movement movement)
{
	std::unique_ptr<JShape> temp_shape = std::make_unique<JShape>(m_points, m_rotation_status);
	temp_shape->move(movement);
	return std::move(temp_shape);
}

void JShape::move(Movement movement)
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

	if (Movement::RotateClockwise == movement)
	{
		_rotate_clockwise();
	}
	if (Movement::RotateCounterClockwise == movement)
	{
		_rotate_counter_clockwise();
	}
}


void JShape::_rotate_clockwise()
{

	switch (m_rotation_status)
	{
	case RotationStatus::FirstState:
		// From FirstState To Right:
		/*
		 *	-#-			#--
		 *	-#-    ->	###
		 *	##-			---
		 */
		m_points[0].set_x(m_points[0].get_x() + 1);
		m_points[0].set_y(m_points[0].get_y() + 1);

		m_points[2].set_x(m_points[2].get_x() - 1);
		m_points[2].set_y(m_points[2].get_y() - 1);

		m_points[3].set_x(m_points[3].get_x());
		m_points[3].set_y(m_points[3].get_y() - 2);

		m_rotation_status = RotationStatus::RotetedRight;
		break;
	case RotationStatus::RotetedRight:
		// From RightState To Inverted:
		/*	#--			-##
		 *	###		->	-#-
		 *	---			-#-
		 */
		m_points[0].set_x(m_points[0].get_x() - 1);
		m_points[0].set_y(m_points[0].get_y() + 1);

		m_points[2].set_x(m_points[2].get_x() + 1);
		m_points[2].set_y(m_points[2].get_y() - 1);

		m_points[3].set_x(m_points[3].get_x() + 2);
		m_points[3].set_y(m_points[3].get_y());

		m_rotation_status = RotationStatus::Inverted;
		break;

	case RotationStatus::Inverted:
		// From Inverted To RotatedLeft:
		/*	-##			---
		 *	-#-  ->		###
		 *	-#-			--#
		 */
		m_points[0].set_x(m_points[0].get_x() - 1);
		m_points[0].set_y(m_points[0].get_y() - 1);

		m_points[2].set_x(m_points[2].get_x() + 1);
		m_points[2].set_y(m_points[2].get_y() + 1);

		m_points[3].set_x(m_points[3].get_x());
		m_points[3].set_y(m_points[3].get_y() + 2);

		m_rotation_status = RotationStatus::RotatedLeft;
		break;

	case RotationStatus::RotatedLeft:
		// From RotatedLeft To FirstState:
		/*	---			-#-
		 *	###		->	-#-
		 *	--#			##-
		 */
		m_points[0].set_x(m_points[0].get_x() + 1);
		m_points[0].set_y(m_points[0].get_y() - 1);

		m_points[2].set_x(m_points[2].get_x() - 1);
		m_points[2].set_y(m_points[2].get_y() + 1);

		m_points[3].set_x(m_points[3].get_x() -2);
		m_points[3].set_y(m_points[3].get_y());

		m_rotation_status = RotationStatus::FirstState;
		break;
	}

}

void JShape::_rotate_counter_clockwise()
{

	switch (m_rotation_status)
	{
	case RotationStatus::RotetedRight:
		// From RotatedRight toFirstState:
		/*
		 *	-#-			#--
		 *	-#-    <-	###
		 *	##-			---
		 */
		m_points[0].set_x(m_points[0].get_x() - 1);
		m_points[0].set_y(m_points[0].get_y() - 1);

		m_points[2].set_x(m_points[2].get_x() + 1);
		m_points[2].set_y(m_points[2].get_y() + 1);

		m_points[3].set_x(m_points[3].get_x());
		m_points[3].set_y(m_points[3].get_y() + 2);

		m_rotation_status = RotationStatus::FirstState;
		break;
	case RotationStatus::Inverted:
		// From Inverted To RotatedRight:
		/*	#--			-##
		 *	###   <-	-#-
		 *	---			-#-
		 */
		m_points[0].set_x(m_points[0].get_x() + 1);
		m_points[0].set_y(m_points[0].get_y() - 1);

		m_points[2].set_x(m_points[2].get_x() - 1);
		m_points[2].set_y(m_points[2].get_y() + 1);

		m_points[3].set_x(m_points[3].get_x() - 2);
		m_points[3].set_y(m_points[3].get_y());

		m_rotation_status = RotationStatus::RotetedRight;
		break;

	case RotationStatus::RotatedLeft:
		// From RotatedLeft to Inverted:
		/*	-##			---
		 *	-#-  <-		###
		 *	-#-			--#
		 */
		m_points[0].set_x(m_points[0].get_x() + 1);
		m_points[0].set_y(m_points[0].get_y() + 1);

		m_points[2].set_x(m_points[2].get_x() - 1);
		m_points[2].set_y(m_points[2].get_y() - 1);

		m_points[3].set_x(m_points[3].get_x());
		m_points[3].set_y(m_points[3].get_y() - 2);

		m_rotation_status = RotationStatus::Inverted;
		break;

	case RotationStatus::FirstState:
		// From FirstState To Left:
		/*	#--			-#-
		 *	###		<-	-#-
		 *	---			##-
		 */
		m_points[0].set_x(m_points[0].get_x() - 1);
		m_points[0].set_y(m_points[0].get_y() + 1);

		m_points[2].set_x(m_points[2].get_x() + 1);
		m_points[2].set_y(m_points[2].get_y() - 1);

		m_points[3].set_x(m_points[3].get_x() + 2);
		m_points[3].set_y(m_points[3].get_y());

		m_rotation_status = RotationStatus::RotatedLeft;
		break;
	}
}
