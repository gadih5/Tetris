#pragma once

#include <string>
#include <vector>
#include <map>

#include "Board.h"
#include "Helpers.h"
#include "GameOverException.h"
#include "ReachedBoardTop.h"

class IPlayer
{
public:
	IPlayer(int id, std::shared_ptr<UtilsIO> io_manager) :
		m_id(id),
		m_player_board(_decide_board_start_point(), io_manager),
		m_name("TempPlayerName")
	{}

	IPlayer(int id, std::string name, std::shared_ptr<UtilsIO> io_manager) :
		m_id(id),
		m_player_board(_decide_board_start_point(), io_manager),
		m_name(name)
	{}

	virtual void play(char movement) = 0;
	virtual void move(Movement movement);
	/*
	 * Function:  set_name
	 * --------------------
	 * Description: This function receives a string
	 *				and sets the player's name to this string.
	 */
	void set_name(std::string name) { m_name = name; }
	/*
	* Function:  draw_board
	* ---------------------
	* Description: This function draws the player's game board.
	*/
	void draw_board() { m_player_board.draw_board(); }
	/*
	* Function:  get_score
	* --------------------
	* Description: This function returns the player's score.
	*
	*  return value: size_t
	*/
	size_t get_score() { return m_player_board.get_score(); }
	/*
	* Function:  get_name
	* --------------------
	* Description: This function returns the playe's name.
	*
	*  return value: string
	*/
	std::string get_name() { return m_name; }

private:
	/*
	* Function:  _decide_board_start_point
	* ------------------------------------
	* Description: This function checks the player's id (1 or 2)
	*				and returns a point according to this id.
	*
	*  return value: Point
	*				  (10,10) for the first player, right side.
	*				  (40,10) for the second player, left side.
	*/
	std::unique_ptr<Point> _decide_board_start_point() { return (m_id == 1 ? std::make_unique<Point>(10, 10) : std::make_unique<Point>(40, 10)); }

protected:
	int m_id;
	Board m_player_board;
	std::string m_name;
};
