#include "ncurses_wrapper.hpp"
#include "tetris.hpp"
#include <ncurses.h>


WINDOW* create_window(int height, int width, int starty, int startx) {
	WINDOW *new_window;

	new_window = newwin(height, width, starty, startx);
	box(new_window, 0 , 0);

	return new_window;
}

int get_color(color_block_t blockColor) {
	switch (blockColor) {
		case GREY:
			return 1;
		case RED:
			return 2;
    	case GREEN:
    		return 3;
    	case BLUE:
    		return 4;
    	case YELLOW:
    		return 5;
    	case PURPLE:
    		return 6;
    	case ORANGE:
    		return 7;
    	case LIGHT_BLUE:
    		return 8;
    	default:
    		return 9;
	}
}

void instantialize_color_pairs() {
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_CYAN, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_BLACK);
}

ncurses_wrapper::ncurses_wrapper()
 : field(create_window(WELL_HEIGHT, WELL_WIDTH, 1, SIDEBAR_WIDTH)),
   bar(create_window(WELL_HEIGHT, SIDEBAR_WIDTH, 1, 0)) {
   	instantialize_color_pairs();
};

ncurses_wrapper::~ncurses_wrapper() {
	delwin(field);
	delwin(bar);
};

void ncurses_wrapper::draw_settled(playField &pf) {
	for (short i = 0; i < WELL_HEIGHT - 1; ++i)
		for (short j = 1; j < WELL_WIDTH - 1; ++j)
			if (pf.gameGrid[i][j] != EMPTY)
				mvwaddch( field, i, j, '#' | COLOR_PAIR(get_color(pf.gameGrid[i][j])) );
}

void ncurses_wrapper::draw_currentBlock(playField &pf) {
	grid_box blocks = pf.currentBlock.get_blocks();
	for (short i = 0; i < BLOCK_SIZE; ++i)
		for (short j = 0; j < BLOCK_SIZE; ++j)
			if (blocks.grid[i][j] != EMPTY)
				mvwaddch( field, pf.currentY + i, pf.currentX + j, '#' | COLOR_PAIR(get_color(blocks.grid[i][j])) );
}

void ncurses_wrapper::draw_preview(sidebar &sb) {
	iBlock next = sb.get_nextBlock();
	grid_box preview = next.get_blocks();
	for (short i = 0; i < BLOCK_SIZE; ++i)
		for (short j = 0; j < BLOCK_SIZE; ++j)
			if (preview.grid[i][j] != EMPTY)
				mvwaddch( bar, i + 3, j + SIDEBAR_WIDTH / 2 - 2, '#' | COLOR_PAIR(get_color(preview.grid[i][j])) );
}

void ncurses_wrapper::draw_playField(playField &pf) {
	werase(field);
	box(field, 0, 0);

	draw_settled(pf);
	draw_currentBlock(pf);

	wrefresh(field);
}

void ncurses_wrapper::draw_sidebar(sidebar &sb) {
	werase(bar);
	box(bar, 0, 0);
	int score = sb.get_score();

	mvwprintw( bar, 1, SIDEBAR_WIDTH / 2 - 5, "Next Block:");
	mvwprintw( bar, WELL_HEIGHT - 8, 1, "F1 = New Game");
	mvwprintw( bar, WELL_HEIGHT - 6, 1, "F3 = Quit");
	
	draw_preview(sb);

	mvwprintw( bar, WELL_HEIGHT - 3, 1, "Score: %d", score);
	wrefresh(bar);
}
