#include "IPlayer.h"

void IPlayer::move(Movement movement)
{
	try
	{
		m_player_board.move_shape(movement);
	}
	catch (ReachedBoardTopException exc)
	{
		throw GameOverException(m_name);
	}
}