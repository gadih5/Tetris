#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int id, std::shared_ptr<UtilsIO> io_manager):
	IPlayer(id, io_manager)
{
	_initalize_name();
	_initalize_keyboard();
}

void HumanPlayer::play(char movement)
{
	// Check that move is valid for this player
	
	if(m_keys.find(movement) == m_keys.end())
	{
		// The key is not relevant for this Player
		return;
	}

	move(m_keys.find(movement)->second);
}

void HumanPlayer::_initalize_name()
{
	//clear_screen();
	std::cout << "Enter Player name" << std::endl;
	std::string player_name = "";
	std::cin >> player_name;
	set_name(player_name);
}

void HumanPlayer::_initalize_keyboard()
{
	if (1 == m_id)
	{
		m_keys = {
		{ 'a', Movement::Left },
		{ 'd', Movement::Right },
		{ 's', Movement::RotateClockwise },
		{ 'w', Movement::RotateCounterClockwise },
		{ 'x', Movement::Drop },
		{ 'A', Movement::Left },
		{ 'D', Movement::Right },
		{ 'S', Movement::RotateClockwise },
		{ 'W', Movement::RotateCounterClockwise },
		{ 'X', Movement::Drop }
		};
	}
	else
	{
		m_keys = {
			{'j', Movement::Left},
			{ 'l', Movement::Right },
			{ 'k', Movement::RotateClockwise },
			{ 'i', Movement::RotateCounterClockwise },
			{ 'm', Movement::Drop },
			{'J', Movement::Left},
			{ 'L', Movement::Right },
			{ 'K', Movement::RotateClockwise },
			{ 'I', Movement::RotateCounterClockwise },
			{ 'M', Movement::Drop }
		};
	}
}