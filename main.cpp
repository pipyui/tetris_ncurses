#include "ncurses_wrapper.hpp"
#include "tetris.hpp"
#include <ncurses.h>


int main(int argc, char *argv[])
{
	int inKey;

	initscr();	// Start curses mode.
	cbreak();	// Line buffering disabled.
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	refresh();

	tetrisGame testgame;
	ncurses_wrapper ncurses;

	ncurses.draw_playField(testgame.well);
	ncurses.draw_sidebar(testgame.sbar);

	bool skip = false;
	bool gameover = false;

	while ((inKey = getch()) != KEY_F(3)) {
		skip = false;
		if (! gameover) {
			switch(inKey) {
				case KEY_LEFT:
					testgame.move_left();
					break;
				case KEY_RIGHT:
					testgame.move_right();
					break;
				case 'z':
					testgame.rotate_left();
					break;
				case 'x':
					testgame.rotate_right();
					break;
				case KEY_DOWN:
					testgame.hard_down();
					testgame.clear_rows();
					testgame.new_block();
					skip = true;
					break;
				case KEY_F(1):
					testgame = tetrisGame();
					skip = true;
					break;
				default:
					skip = true;
					break;
			}
			if (! skip &&! testgame.move_down()) {
				testgame.clear_rows();
				testgame.new_block();
			}

			if (testgame.check_gameover()) {
				mvprintw(WELL_HEIGHT / 2, (WELL_WIDTH + SIDEBAR_WIDTH) / 2 - 3, "GAME OVER!");
				gameover = true;
			}

			ncurses.draw_playField(testgame.well);
			ncurses.draw_sidebar(testgame.sbar);
			refresh();

		} else {
			if (inKey == KEY_F(1)) {
				testgame = tetrisGame();
				gameover = false;
				ncurses.draw_playField(testgame.well);
				ncurses.draw_sidebar(testgame.sbar);
				refresh();
			}

		}
	}
		
	endwin();			/* End curses mode		  */
	return 0;
}
