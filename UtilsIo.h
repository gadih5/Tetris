#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "Config.h"
#include "Color.h"


class UtilsIO
{
public:

	UtilsIO(bool is_colored) :
		m_color_mode(is_colored),
		m_random_every_time(false),
		m_regular_color(Color::WHITE)
	{}

	void set_color_mode(bool color_mode);
	void set_party_mode(bool party) { m_random_every_time = party; }
	void set_text_color(Color colorToSet);
	void gotoxy(int x, int y);
	void hide_cursor();
	void clear_screen();
	/*
	* Function:  get_color
	* --------------------
	* Description: This function returns WHITE color, or in color mode returns a random color.
	*
	*  return value: Color:
	*				  (LIGHTBLUE/YELLOW/LIGHTRED/LIGHTCYAN/LIGHTGREEN/LIGHTBLUE/LIGHTMAGENTA/LIGHTGREY/WHITE)
	*/
	Color get_color();
	/*
	* Function:  FUNC_NAME
	* --------------------
	* Description: This function returns a random color.
	*
	*  return value: Color:
	*				  (LIGHTBLUE/YELLOW/LIGHTRED/LIGHTCYAN/LIGHTGREEN/LIGHTBLUE/LIGHTMAGENTA/LIGHTGREY/WHITE)
	*/
	Color randomise_color();

private:
	Color m_regular_color;
	bool m_color_mode;
	bool m_random_every_time;
};

void independent_gotoxy(int x, int y);

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);

#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif

#endif