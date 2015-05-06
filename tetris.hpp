#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "tetris.hpp"


constexpr short WELL_HEIGHT = 21;   // 20 + 1 bottom collider
constexpr short WELL_WIDTH = 12;    // 10 + 2 side colliders
constexpr short BLOCK_SIZE = 3;

struct grid_box {
    short grid[BLOCK_SIZE][BLOCK_SIZE];
};

class iBlock {
    // Grant playField private access.
    friend class playField;
private:
	short id; // Piece id, used to indicate what kind of block it is.
	grid_box blocks;

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
	short gameGrid[WELL_HEIGHT][WELL_WIDTH];
	iBlock currentBlock;

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

    bool check_collision();
    void clear_row(int);
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
