#pragma once
#include "Point.h"
#include "Shape.h"
#include "ShapeFactory.h"

class Board
{
public:
	Board(std::unique_ptr<Point> starting_point, std::shared_ptr<UtilsIO> io_manager);

	//Board(const Point& starting_point, std::unique_ptr<Shape> shape);

	void delete_shape_from_board();

	void move_shape(Movement movement);
	void draw_board();
	/*
	* Function:  get_score
	* --------------------
	* Description: This function returns the board's score.
	*
	*  return value: size_t
	*/
	size_t get_score() { return m_score; }

	/*
	* Function:  _drop_shape
	* -----------------------
	* Description: This function continually drops Tetris shape (in the board),
	*			    until the shape is landed.
	*/
	void _drop_shape();

private:
	// Printing function
	/*
	* Function: _draw_shape_in_board
	* ----------------------
	* Description: This function marks shape in board. optional - print the new board (is_draw control it)
	*/
	void _draw_shape_in_board(bool is_draw);
	/*
	* Function: _delete_shape_from_board
	* ----------------------
	* Description: This function marks shape as deleted in board. optional - print the new board (is_draw control it)
	*/
	void _delete_shape_from_board(bool is_draw);
	/*
	* Function: _mark_shape_in_board
	* ----------------------
	* Description: This function marks shape in board (change the char according to coordinate in m_board)
	*/
	void _mark_shape_in_board(char figure, bool is_draw);
	/*
	* Function: _print_frame
	* ----------------------
	* Description: This function prints the frame of the board.
	*/
	void _print_frame();
	/*
	Function:  _print_board_in_place
	* --------------------------------
	* Description: This function receives a coordinates and prints a board from there.
	*/
	void _print_board_in_place(int raw, int col);
	/*
	* Function:  _print_board_score
	* -----------------------------
	* Description: This function prints the player's current score.
	*/
	void _print_board_score();

	// Business Logic Functions
	bool _is_valid_move(std::unique_ptr<Shape> fetched_shape);
	/*
	* Function:  _is_gameover
	* ------------------------
	* Description: This function checks if the board is full.
	*
	*  return value: bool
	*                True for gameover.
	*/
	bool _is_gameover();

	/*
	* Function:  _clear_full_lines
	* -----------------------------
	* Description: This function checks if there are full lines at the board
	*				and clears those lines.
	*/
	void _clear_full_lines();

	/*
	* Function:  _is_line_full
	* -------------------------
	* Description: This function receives a row's index (of the board) and checks if this line is full.
	*				if the checked line is full the player's score is raise.
	*
	*  return value: bool
	*                True for a full line.
	*/
	bool _is_line_full(size_t row_index);

	/*
	* Function:  _clear_line
	* -----------------------
	* Description: This function receives a row's index
	*				and clears this line.
	*/
	void _clear_line(size_t row_index);

	/*
	* Function:  _move_shape_with_draw
	* --------------------------------
	* Description: This function receives a movement,
	*				erases the shape from the board and prints the shape at the new position (according to the movement).
	*/
	void _move_shape_with_draw(Movement movement);

	/*
	* Function:  _is_landed
	* -------------------------
	* Description: This function check if m_current_shape reached board bottom
	*
	*  return value: bool
	*                True for landed
	*/
	virtual bool _is_landed();

	// Const board size, as defined in exercise
	enum BoardSizes : size_t
	{
		HEIGHT = 18,
		WIDTH = 12
	};

	// Score definition
	enum Score : size_t
	{
		ShapeLanded = 10,
		LineFull = 10 * WIDTH
	};
	// Define chars state in board
	enum ShapesChars : char
	{
		// Adding 2 for boarders..
		MovingShape = '*',
		LandedShape = '#',
		EmptyChar = ' '
	};

private:
	char m_board[BoardSizes::WIDTH][BoardSizes::HEIGHT];
	std::unique_ptr<Shape> m_current_shape;
	const Point m_starting_point;
	std::shared_ptr<UtilsIO> m_io_manager;
	ShapeFactory m_shape_factory;
	size_t m_score;
};
