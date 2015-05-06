#include "tetris.hpp"
#include <cstdlib>


// iBlock stuff
iBlock::iBlock()
 : id(std::rand() % 7) { setBlock(); };

// Input is number 0-6, to determine kind of block.
iBlock::iBlock(short i) : id(i) { setBlock(); };

void iBlock::setBlock() {
	switch (id) {
		// I
        case 0:
            blocks.grid[0][0] = 1;
            blocks.grid[1][0] = 1;
            blocks.grid[2][0] = 1;
            //blocks.grid[3][0] = 1;
        	break;
        // J
        case 1:
            blocks.grid[0][0] = 2;
            blocks.grid[1][0] = 2;
            blocks.grid[1][1] = 2;
            blocks.grid[1][2] = 2;
        	break;
        // L
        case 2:
            blocks.grid[0][2] = 3;
            blocks.grid[1][0] = 3;
            blocks.grid[1][1] = 3;
            blocks.grid[1][2] = 3;
        	break;
        // O
        case 3:
            blocks.grid[0][0] = 4;
            blocks.grid[0][1] = 4;
            blocks.grid[1][0] = 4;
            blocks.grid[1][1] = 4;
        	break;
        // S
        case 4:
            blocks.grid[0][1] = 5;
            blocks.grid[0][2] = 5;
            blocks.grid[1][0] = 5;
            blocks.grid[1][1] = 5;
        	break;
        // T
        case 5:
            blocks.grid[0][1] = 6;
            blocks.grid[1][0] = 6;
            blocks.grid[1][1] = 6;
            blocks.grid[1][2] = 6;
        	break;
        // Z
        case 6:
            blocks.grid[0][0] = 7;
            blocks.grid[0][1] = 7;
            blocks.grid[1][1] = 7;
            blocks.grid[1][2] = 7;
        	break;
        default:
        	break;
   }
}

void playField::rotate(bool left) {

}

void iBlock::clearGrid() {
	for (short i = 0; i < BLOCK_SIZE; ++i)
		for (short j = 0; j < BLOCK_SIZE; ++j)
			blocks.grid[i][j] = 0;
}

grid_box iBlock::getBlocks() const {
    return blocks;
}

// playField stuff
void playField::build_well() {
    for (int i = 0; i < WELL_HEIGHT; ++i) {
        gameGrid[i][0] = 8;
        gameGrid[i][WELL_WIDTH - 1] = 8;
    }
    for (int i = 0; i < WELL_WIDTH; ++i)
        gameGrid[WELL_HEIGHT - 1][i] = 8;
}

playField::playField()
 : currentBlock(iBlock()) { build_well(); };

// sidebar stuff
sidebar::sidebar()
 : score(0), nextBlock(iBlock()) {};
