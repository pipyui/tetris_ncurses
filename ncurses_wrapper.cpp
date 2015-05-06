#include "ncurses_wrapper.hpp"
#include "tetris.hpp"
#include <ncurses.h>


WINDOW* create_window(int height, int width, int starty, int startx) {
	WINDOW *new_window;

	new_window = newwin(height, width, starty, startx);
	box(new_window, 0 , 0);

	return new_window;
}

ncurses_wrapper::ncurses_wrapper()
 : field(create_window(WELL_HEIGHT, WELL_WIDTH, 1, 0)),
   bar(create_window(WELL_HEIGHT, SIDEBAR_WIDTH, 1, WELL_WIDTH + 1)) {};

ncurses_wrapper::~ncurses_wrapper() {
	delwin(field);
	delwin(bar);
};

void ncurses_wrapper::draw_playField(playField &pf) {

}

void ncurses_wrapper::draw_sidebar(sidebar &sb) {

}
