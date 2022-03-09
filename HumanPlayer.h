#pragma once


#include "IPlayer.h"

class HumanPlayer :
	public IPlayer
{
public:
	HumanPlayer(int id, std::shared_ptr<UtilsIO> io_manager);
	virtual ~HumanPlayer() = default;

	virtual void play(char move) override;

private:
	/*
	* Function:  _initalize_name
	* --------------------------
	* Description: This function asks the user for a name and sets it in the player's name.
	*/
	void _initalize_name();
	/*
	* Function:  _initalize_keyboard
	* --------------------------
	* Description: This function initializes the player's movement keys (for each player different keys).
	*/
	void _initalize_keyboard();

private:
	std::map<char, Movement> m_keys;
};
