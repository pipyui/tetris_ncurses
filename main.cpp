#include "ncurses_wrapper.hpp"
#include "tetris.hpp"
#include <ncurses.h>


int main(int argc, char *argv[])
{
	int ch;

	initscr();	// Start curses mode.
	cbreak();	// Line buffering disabled.
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	refresh();

	instantialize_color_pairs();

	tetrisGame testgame;
	ncurses_wrapper ncurses;

	ncurses.draw_playField(testgame.well);
	ncurses.draw_sidebar(testgame.sbar);

	while((ch = getch()) != KEY_F(1));
		
	endwin();			/* End curses mode		  */
	return 0;
}
