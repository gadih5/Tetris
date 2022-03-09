#include "TetrisGame.h"
#include "HumanPlayer.h"

TetrisGame::TetrisGame() :
	m_paused(false),
	m_io_manager(std::make_shared<UtilsIO>(false)),
	m_speed_level(Speed::Normal),
	m_single_mode(false)
{
	m_io_manager->hide_cursor();
}

void TetrisGame::start()
{
	_menu();
}

void TetrisGame::_menu()
{
	char user_choice = 'A';
	while('9'!=user_choice)
	{
		
		m_io_manager->clear_screen();
		m_io_manager->gotoxy(0, 0);
		m_io_manager->set_text_color(Color::WHITE);
		std::cout << "Welcome to our Tetris Game! Lets get started." << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(1) Start a new game" << std::endl;
		if (m_paused)
		{
			std::cout << "(2) Continue a paused game" << std::endl;
		}

		std::cout << "(3) Change game colors" << std::endl;
		std::cout << "(4) Change game speed" << std::endl;
		std::cout << "(5) For one player mode" << std::endl;
		std::cout << "(8) Show instructions and keys" << std::endl;
		std::cout << "(9) Exit" << std::endl;
		std::cin >> user_choice;
		m_io_manager->clear_screen();
		_execute_choice(user_choice);
	}
}

bool TetrisGame::_execute_choice(char user_choice)
{
	switch (user_choice)
	{
	case '1':
		m_single_mode = false;
		_start_new_game();
		break;

	case '2':
		_continue_paused_game();
		break;
	case '3':
		_manage_colors();
		break;
	case '4':
		_manage_speed();
		break;
	case '5':
		m_single_mode = true;
		_play_one_player();
		break;
	case '8':
		_show_instructions();
		break;
	case '9':
		return false;
	default:
		std::cout << "OOPSSSssssi. No such option. Try again." << std::endl;
		return false;
	}
	return true;
}

// Option 1 - Play new game
void TetrisGame::_start_new_game()
{
	// Choosing players
	m_player1 = _choose_player(FirstPlayer);
	// Choose second player
	m_player2 = _choose_player(SecondPlayer);
	_play();
}

void TetrisGame::_play_one_player()
{
	// Choosing player
	m_player1 = _choose_player(FirstPlayer);
	m_io_manager->clear_screen();
	_play_one_player_mode();
}

// Option 2 - Continue a paused game
void TetrisGame::_continue_paused_game()
{
	// Safety issues.`
	if(m_paused)
	{
		if(m_single_mode)
		{
			m_io_manager->clear_screen();
			_play_one_player_mode();
		}
		else
		{
			m_io_manager->clear_screen();
			_play();
		}
	}
}

// Option 3 - Manage colors
void TetrisGame::_manage_colors()
{
	char user_choice = 'A';

	while ('9' != user_choice)
	{
		std::cout << "What kind of colorful game would you like?" << std::endl;
		std::cout << "(1) Party. I want my game to dance" << std::endl;
		std::cout << "(2) One boring color.." << std::endl;
		std::cout << "(3) White color (default)" << std::endl;

		std::cout << "(9) Exit" << std::endl;
		std::cin >> user_choice;
		bool valid_color_choise = _execute_color_choice(user_choice);
		if(valid_color_choise)
		{
			user_choice = '9';
		}
		else
		{
			m_io_manager->clear_screen();
			std::cout << "Invalid choice. ";
		}
	}
}

// Option 4 - Manage speed
void TetrisGame::_manage_speed()
{
	char user_choice = 'A';

	while ('9' != user_choice)
	{
		std::cout << "What is your level?" << std::endl;
		std::cout << "(1) I am a LEGEND. You can call me the Tetris Hendrix" << std::endl;
		std::cout << "(2) Lets say that my friends will tell I'm a PRO" << std::endl;
		std::cout << "(3) Not bad" << std::endl;
		std::cout << "(4) Amateur" << std::endl;
		std::cout << "(5) I want to decide by myself." << std::endl;

		std::cin >> user_choice;
		bool valid_color_choise = _execute_speed_choice(user_choice);
		if (valid_color_choise)
		{
			user_choice = '9';
		}
		else
		{
			m_io_manager->clear_screen();
			std::cout << "Invalid choice. ";
		}
	}
}

bool TetrisGame::_execute_color_choice(char user_choice)
{
	if('1' == user_choice)
	{
		m_io_manager->set_color_mode(true);
		m_io_manager->set_party_mode(true);
		return true;
	}
	if('2' == user_choice)
	{
		m_io_manager->set_color_mode(true);
		m_io_manager->set_party_mode(false);
		return true;
	}
	if ('3' == user_choice)
	{
		m_io_manager->set_color_mode(false);
		m_io_manager->set_party_mode(false);
		return true;
	}
	
	return false;
}


bool TetrisGame::_execute_speed_choice(char user_choice)
{
	if('1' != user_choice &&
		'2' != user_choice &&
		'3' != user_choice &&
		'4' != user_choice &&
		'5' != user_choice)
	{
		return false;
	}
	switch (user_choice)
	{
	case '1':
		m_speed_level = Speed::Legend;
		break;
	case '2':
		m_speed_level = Speed::Pro;
		break;
	case '3':
		m_speed_level = Speed::Normal;
		break;
	case '4':
		m_speed_level = Speed::Amateur;
		break;
	case '5':
		std::cout << "Enter your desired speed, in scale of 1 to ten. 1 is fastest, 10 for slowest: ";
		size_t desired_speed = 2000;
		std::cin >> desired_speed;
		if (desired_speed > 10 || desired_speed < 1)
			return false;
		m_speed_level =  2000 * desired_speed;
		break;
	}
	
	return true;
}


// Option 8 - show instructions
void TetrisGame::_show_instructions()
{
	std::cout << "Welcome!" << std::endl;
	std::cout << "There is two boards in this game. You can choose also the one player mode, if desired." << std::endl;
	std::cout << "You can set the game speed & color - see menu." << std::endl;
	std::cout << "Left player should play with the following keys." << std::endl;
	std::cout << "		- A or a for Left" << std::endl;
	std::cout << "		- D or d for Right" << std::endl;
	std::cout << "		- S or s for Rotate clockwise" << std::endl;
	std::cout << "		- W or w for Rotate counterclockwise" << std::endl;
	std::cout << "		- X or x for Drop" << std::endl;
	std::cout << "Right player should play with the following keys." << std::endl;
	std::cout << "		- J or j for Left" << std::endl;
	std::cout << "		- L or l for Right" << std::endl;
	std::cout << "		- K or k for Rotate clockwise" << std::endl;
	std::cout << "		- I or i for Rotate counterclockwise" << std::endl;
	std::cout << "		- M or m for Drop" << std::endl;
	std::cout << "Press Any key to go back to Menu" << std::endl;
	while(!_kbhit())
	{}
}

/*********************************************************************************************
	Helping functions
*********************************************************************************************/
std::unique_ptr<IPlayer> TetrisGame::_choose_player(int id)
{
	std::unique_ptr<IPlayer> return_value = std::make_unique<HumanPlayer>(id, m_io_manager);
	return std::move(return_value);
}


void TetrisGame::_play()
{
	bool game_over = false;
	char key = 0;
	int i = 0;
	m_io_manager->clear_screen();
	m_player1->draw_board();
	m_player2->draw_board();

	try
	{
		do {
			if (_kbhit())
			{
				key = _getch();
				m_player1->play(key);
				m_player2->play(key);
				//	Sleep(100);

			}
			i++;
			if (0 == i % m_speed_level)
			{
				m_player1->move(Movement::Down);
				m_player2->move(Movement::Down);

			}


		} while (key != ESC);
	}
	catch (const GameOverException& exc)
	{
		game_over = true;
		m_paused = false;
		_handle_game_over(exc.who_lost());


	}
	if(ESC == key &&
		!game_over)
	{
		m_paused = true;
	}
}


void TetrisGame::_play_one_player_mode()
{
	bool game_over = false;
	char key = 0;
	int i = 0;
	m_player1->draw_board();

	try
	{
		do {
			if (_kbhit())
			{
				key = _getch();
				m_player1->play(key);
			}
			i++;
			if (0 == i % m_speed_level)
			{
				m_player1->move(Movement::Down);
			}
		} while (key != ESC);
	}
	catch (const GameOverException& exc)
	{
		game_over = true;
		m_paused = false;
		m_io_manager->clear_screen();
		m_io_manager->gotoxy(0, 0);

		std::cout << "One player.. so there is no winner (or looser)" << std::endl;;
		std::cout << "Your score is: " << m_player1->get_score() << std::endl;
		std::cout << "Press any key and then Enter in order to go back to menu" << std::endl;
		std::string x;
		std::cin >> x;
	}
	if (ESC == key &&
		!game_over)
	{
		m_paused = true;
	}
}


void TetrisGame::_handle_game_over(std::string player_name)
{
	m_io_manager->clear_screen();
	m_io_manager->gotoxy(0, 0);
	std::cout << player_name << " board is full..";
	Sleep(1000);
	std::cout << "But in this game - only score count" << std::endl;
	Sleep(1000);
	size_t player_one_score = m_player1->get_score();
	size_t player_two_score = m_player2->get_score();
	if (player_one_score == player_two_score)
	{
		std::cout << "It's a TIE! Unbelievable!" << std::endl;
	}
	else
	{
		std::string winner = player_one_score > player_two_score ? m_player1->get_name() : m_player2->get_name();
		std::cout << "And the winner is........";
		Sleep(1000);
		std::cout << winner << std::endl;
	}

	std::cout << "Press any key and then Enter in order to go back to menu" << std::endl;
	std::string x;
	std::cin >> x;
}