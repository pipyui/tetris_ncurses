#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "tetris.hpp"


constexpr short WELL_HEIGHT = 21;   // 20 + 1 bottom collider
constexpr short WELL_WIDTH = 12;    // 10 + 2 side colliders
constexpr short BLOCK_SIZE = 4;     // Max dimensions of iBlock

// Abstraction for single brick.
enum color_block_t {
    EMPTY,
    GREY,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    ORANGE,
    LIGHT_BLUE
};

struct grid_box {
    color_block_t grid[BLOCK_SIZE][BLOCK_SIZE];
};

class iBlock {
    // Grant playField private access.
    friend class playField;
private:
	short id; // Piece id, used to indicate what kind of block it is.
	grid_box blocks;

    void rejustify();
    bool empty_row(short) const;
    bool empty_col(short) const;
    void delete_row(short);
    void delete_col(short);

public:
    iBlock();

    // Input is number 0-6, to determine kind of block.
    iBlock(short);

	void set_block();
    void clear_grid();
    grid_box get_blocks() const;
    short get_id() const;
};

class playField {
    friend class ncurses_wrapper;
private:
	color_block_t gameGrid[WELL_HEIGHT][WELL_WIDTH];
	iBlock currentBlock;
    short currentX;
    short currentY;

    void build_well();  // Will be used by constructor only.

public:
    playField();
    //~playField();

    // Actions on iBlock currentBlock.
    void rotate(bool);
    void move_left();
    void move_right();
    bool move_down();
    void hard_down();

    void settle_block();

    void clear_grid();
    bool check_collision() const;
    bool check_full_row(short) const;
    void clear_row(short);
    short check_and_clear_rows();
    void new_block();
    void new_block(short);

    color_block_t block_at(short, short) const;
    iBlock get_currentBlock() const;
    short get_currentX() const;
    short get_currentY() const;
    bool check_gameover() const;
};

class sidebar {
private:
	int score;
	iBlock nextBlock;

public:
    sidebar();
    //~sidebar();
    int bump_score();
    int bump_score(short);
    void new_block();

    int get_score() const;
    iBlock get_nextBlock() const;
    short get_nextBlock_id() const;
};

class tetrisGame {
public:
    playField well;
    sidebar sbar;

    tetrisGame();
    //~tetrisGame();

    void rotate_left();
    void rotate_right();
    void move_left();
    void move_right();
    bool move_down();
    void hard_down();


    void clear_row(short);
    void clear_rows();
    void new_block();
    bool check_gameover() const;
    int get_score() const;
};

#endif
