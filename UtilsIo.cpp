#include "UtilsIo.h"

#ifndef WINDOWS

class UtilsIO
{
public:

	UtilsIO(bool color_mode) : m_color_mode(color_mode) {}

	void set_color_mode(bool color_mode) {}
	void set_text_color(Color colorToSet) {}
	void hide_cursor() {}
	void clear_screen() {}
	void gotoxy(int x, int y) {}
	Color get_color()

private:
	Color randomise_color() { return Color::WHITE; }

private:
	bool m_color_mode;
};

int _getch(void) { return 0; }
int _kbhit(void) { return 0; }
void Sleep(unsigned long) {}

#else

void UtilsIO::gotoxy(int x, int y)
{
	if (m_color_mode)
	{
		if (m_random_every_time)
		{
			set_text_color(randomise_color());
		}
		else
		{
			set_text_color(m_regular_color);
		}
		
	}
	

	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout << std::flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void UtilsIO::set_color_mode(bool color_mode)
{
	m_color_mode = color_mode;
	if (!color_mode)
	{
		set_text_color(Color::WHITE);
	}
	else
	{
		m_regular_color = randomise_color();
	}
}

void UtilsIO::set_text_color(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void UtilsIO::hide_cursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

Color UtilsIO::get_color()
{
	if (!m_color_mode)
	{
		return Color::WHITE;
	}
	return randomise_color();
}

void UtilsIO::clear_screen()
{
	system("cls");
}

Color UtilsIO::randomise_color()
{
	int random_number = std::rand() % 8;

	switch (random_number)
	{
	case 0:
		return Color::LIGHTBLUE;
	case 1:
		return Color::YELLOW;
	case 2:
		return Color::LIGHTRED;
	case 3:
		return Color::LIGHTCYAN;
	case 4:
		return Color::LIGHTGREEN;
	case 5:
		return Color::LIGHTBLUE;
	case 6:
		return Color::LIGHTMAGENTA;
	case 7:
		return Color::LIGHTGREY;
	default:
		return Color::WHITE;
	}
}

#endif

void independent_gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout << std::flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

