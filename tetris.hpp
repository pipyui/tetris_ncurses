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

	void setBlock();
    void clearGrid();
    grid_box getBlocks() const;
};

class playField {
private:
	color_block_t gameGrid[WELL_HEIGHT][WELL_WIDTH];
	iBlock currentBlock;
    short currentX;
    short currentY;

    void build_well();

public:
    playField();
    ~playField();

    // Actions on iBlock currentBlock.
    void rotate(bool);
    void move_left();
    void move_right();
    void move_down();
    void hard_down();

    color_block_t block_at(short, short) const;
    bool check_collision() const;
    void clear_row(short);
};

class sidebar {
private:
	int score;
	iBlock nextBlock;

public:
    sidebar();
    ~sidebar();
};

#endif
