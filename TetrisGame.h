#pragma once

#include <functional>
#include <map>
#include "IGame.h"
#include "IPlayer.h"
#include "UtilsIo.h"

enum PlayerID
{
	FirstPlayer = 1,
	SecondPlayer = 2
};

enum Speed : size_t
{
	Legend = 6000,
	Pro = 9000,
	Normal = 14000,
	Amateur = 20000
};

class TetrisGame :
	public IGame
{
public:
	TetrisGame();

	virtual void start();

private:
	/*
	* Function:  _menu
	* -----------------------------
	* Description: This function presents the game's main menu,
	*			    and asks the user to choose an option (or exit).
	*/
	void _menu();

	/*
	* Function:  _start_new_game
	* ---------------------------
	* Description: This function starts two players mode game.
	*/

	void _start_new_game();
	/*
	* Function: _execute_choice
	* -------------------------
	* Description: This function receives a character (the user's option choice)
	*              and executes the choosen option.
	*
	*  return value: bool
	*				  False for invalid input.
	*/
	bool _execute_choice(char user_choice);

	/*
	* Function: _continue_paused_game
	* -------------------------------
	* Description: This function returns to the game's board status before the game has stopped, and continues the game.
	*/
	void _continue_paused_game();
	/*
	* Function:  _show_instructions
	* -----------------------------
	* Description: This function presents the game's instructions: game's options and player's movement keys.
	*/
	void _show_instructions();

	/*
	* Function:  _manage_colors
	* -------------------------
	* Description: This function presents the optional colors modes and asks the user to choose one of them,
	*				or go back to the main menu.
	*/
	void _manage_colors();
	/*
	* Function:  _manage_speed
	* -------------------------
	* Description: This function presents the optional speed modes and asks the user to choose one of them,
	*				or go back to the main menu.
	*/
	void _manage_speed();

	std::unique_ptr<IPlayer> _choose_player(int player_id);
	/*
	* Function:  _execute_color_choice
	* --------------------------------
	* Description: This function receives a character (the user's color mode choice)
	*				and sets the chosen game color.
	*
	*  return value: bool
	*				  False for invalid input.
	*/
	bool _execute_color_choice(char user_choice);

	/*
	* Function:  _execute_speed_choice
	* --------------------------------
	* Description: This function receives a character (the user's speed mode choice)
	*				and sets the chosen game speed.
	*
	*  return value: bool
	*				  False for invalid input.
	*/
	bool _execute_speed_choice(char user_choice);
	/*
	* Function:  _play
	* --------------------
	* Description: This function continually drops Tetris shapes (in two boards) and recevies users's moves,
	*			    until one of the board is full or one of the users paused the game (clicked ESC).
	*/
	void _play();
	/*
	* Function:  _play_one_player
	* ---------------------------
	* Description: This function starts one player mode game.
	*/
	void _play_one_player();
	/*
	* Function:  _play_one_player_mode
	* --------------------------------
	* Description: This function continually drops Tetris shapes and recevies user's moves,
	*			    until the board is full or the user paused the game (clicked ESC).
	*/
	void _play_one_player_mode();

	/*
	* Function:  _handle_game_over
	* ----------------------------
	* Description: This function receives the name of the player that has a full board,
	*				and announces the winner by score.
	*/
	void _handle_game_over(std::string player_name);

private:
	std::unique_ptr<IPlayer> m_player1;
	std::unique_ptr<IPlayer> m_player2;
	bool m_paused;
	std::shared_ptr<UtilsIO> m_io_manager;
	size_t m_speed_level;
	bool m_single_mode;
	//State m_current_game;
};
