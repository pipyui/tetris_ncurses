#ifndef NCURSES_WRAPPER_HPP
#define NCURSES_WRAPPER_HPP

#include "ncurses_wrapper.hpp"
#include "tetris.hpp"
#include <ncurses.h>


constexpr short SIDEBAR_WIDTH = 15;

WINDOW* create_window(int height, int width, int starty, int startx);
int get_color(color_block_t);
void instantialize_color_pairs();

class ncurses_wrapper {
private:
	WINDOW *field;
	WINDOW *bar;

	void draw_settled(playField &);
	void draw_currentBlock(playField &);
	void draw_preview(sidebar &);

public:
	ncurses_wrapper();
	~ncurses_wrapper();

	void draw_playField(playField &);
	void draw_sidebar(sidebar &);
};

#endif
