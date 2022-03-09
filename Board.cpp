#include "Board.h"

#include "GameOverException.h"
#include "ReachedBoardTop.h"


Board::Board(std::unique_ptr<Point> starting_point, std::shared_ptr<UtilsIO> io_manager) :
	m_shape_factory(),
	m_board(),
	m_starting_point(Point(starting_point->get_x(), starting_point->get_y())),
	m_io_manager(io_manager),
	m_score(0)
{
	int row_index = 0;
	int col_index = 0;

	// Now define edges:
	int first_row = 0;
	int first_col = 0;
	int last_row = HEIGHT - 1;
	int last_col = WIDTH - 1;

	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			m_board[i][j] = EmptyChar;
		}
	}

	m_current_shape = std::move(m_shape_factory.create_shape(Point(WIDTH / 2, 0, MovingShape)));
	//draw_board();
}

void Board::draw_board()
{
	_print_frame();
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			_print_board_in_place(i, j);
		}
	}
	_mark_shape_in_board(MovingShape, true);
	_print_board_score();
}

void Board::move_shape(Movement movement)
{
	// If Shape needs to go down and can't.. drop need to be done
	auto fetched_shape = m_current_shape->fetch_move(movement);
	if (Movement::Down == movement &&
		m_current_shape->compare(fetched_shape->get_points()))
	{
		movement = Movement::Drop;
	}

	if (Movement::Drop == movement)
	{
		_drop_shape();
	}
	else
	{
		// Delete here the shape because in _is_valid_move & _is_landed we check if there is any '*' in shape's place. Notice: Doesn't clear the print.
		_delete_shape_from_board(false);
		if (_is_valid_move(std::move(fetched_shape)))
		{
			// Move can't be done.
			_move_shape_with_draw(movement);
		}
		else
		{
			_delete_shape_from_board(true);
		}
	}

	// Check if landed
	if (_is_landed())
	{
		_mark_shape_in_board(LandedShape, true);
		m_current_shape.release();
		m_current_shape = std::move(m_shape_factory.create_shape(Point(WIDTH / 2, 0, '*')));
		_clear_full_lines();
		m_score+=Score::ShapeLanded;
	}

	if (_is_gameover())
	{
		throw ReachedBoardTopException();
	}

	_mark_shape_in_board(MovingShape, true);

	_print_board_score();
}

void Board::_clear_full_lines()
{
	// While last line full, we clear it.. 
	for (size_t i = 0; i < HEIGHT; i++)
	{
		if (_is_line_full(i))
		{
			_clear_line(i);
		}
	}
}

// Clear line and arrange all the line above
void Board::_clear_line(size_t full_row)
{
	char board_copy[WIDTH][HEIGHT];
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			board_copy[i][j] = m_board[i][j];
		}
	}
	
	for (size_t row = 1; row <= full_row; row++)
	{
		for (size_t i = 0; i < WIDTH; i++)
		{
			m_board[i][row] = board_copy[i][row - 1];
			_print_board_in_place(i, row);
		}
	}
	// The top line become Empty chars..
	for (size_t i = 0; i < WIDTH; i++)
	{
		m_board[i][0] = EmptyChar;
		_print_board_in_place(i, 0);
	}
}
bool Board::_is_line_full(size_t row_index)
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		if (EmptyChar == m_board[i][row_index])
		{
			return false;
		}
	}

	m_score += Score::LineFull;
	return true;
}

bool Board::_is_gameover()
{
	// If where we creating the shape is contain '#', Game over..
	if (LandedShape == m_board[WIDTH / 2][0])
	{
		return true;
	}
	return false;
}

bool Board::_is_valid_move(std::unique_ptr<Shape> fetched_shape)
{
	for (const auto& point : fetched_shape->get_points())
	{
		// Out of board borders (From left or right side)
		if (
			point.get_x() >= BoardSizes::WIDTH ||
			point.get_x() < 0)
		{
			return false;
		}

		// Overriding current board shape..
		if ('#' == m_board[point.get_x()][point.get_y()])
		{
			return false;
		}

	}
	return true;
}

void Board::_drop_shape()
{
	while (!_is_landed())
	{
		_move_shape_with_draw(Movement::Down);
	}
}

bool Board::_is_landed()
{
	for (auto& point : m_current_shape->get_points())
	{
		// Check if :	one of shape's point has reached to bottom of the board OR
		//				one of shape point's is going to touch other shape in board, after the next down move, 
		if (BoardSizes::HEIGHT - 1 == point.get_y() || LandedShape == m_board[point.get_x()][point.get_y() + 1])
		{
			return true;
		}
	}
	return false;
}

void Board::_draw_shape_in_board(bool is_draw)
{
	_mark_shape_in_board(MovingShape, is_draw);
}

void Board::_delete_shape_from_board(bool is_draw)
{
	_mark_shape_in_board(EmptyChar, is_draw);
}

void Board::_mark_shape_in_board(char figure, bool is_draw)
{
	for (const auto& point : m_current_shape->get_points())
	{
		m_board[point.get_x()][point.get_y()] = figure;
		if (is_draw)
		{
			_print_board_in_place(point.get_x(), point.get_y());
		}
	}
}

void Board::_print_board_in_place(int raw, int col)
{
	m_io_manager->gotoxy(raw + m_starting_point.get_x(), col + m_starting_point.get_y());
	std::cout << m_board[raw][col];
}

void Board::_print_frame()
{
	for (size_t i = 0; i < BoardSizes::WIDTH; i++)
	{
		m_io_manager->gotoxy(m_starting_point.get_x() + i, m_starting_point.get_y() + HEIGHT);
		std::cout << '^';
	}
	for (size_t i = 0; i < BoardSizes::HEIGHT; i++)
	{
		m_io_manager->gotoxy(m_starting_point.get_x() - 1, m_starting_point.get_y() + i);
		std::cout << '|';

		m_io_manager->gotoxy(m_starting_point.get_x() + BoardSizes::WIDTH, m_starting_point.get_y() + i);
		std::cout << '|';
	}
}

void Board::_move_shape_with_draw(Movement movement)
{
	_delete_shape_from_board(true);
	m_current_shape->move(movement);
}

void Board::_print_board_score()
{
	m_io_manager->gotoxy(m_starting_point.get_x(), m_starting_point.get_y() - 4 );
	std::cout << "Score is: " << m_score;
}
