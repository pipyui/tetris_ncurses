#ifndef NCURSES_WRAPPER_HPP
#define NCURSES_WRAPPER_HPP

#include "ncurses_wrapper.hpp"
#include "tetris.hpp"
#include <ncurses.h>


constexpr short SIDEBAR_WIDTH = 20;

WINDOW* create_window(int height, int width, int starty, int startx);

class ncurses_wrapper {
private:
	WINDOW *field;
	WINDOW *bar;

public:
	ncurses_wrapper();
	~ncurses_wrapper();

	void draw_playField(playField &);
	void draw_sidebar(sidebar &);
};

#endif
