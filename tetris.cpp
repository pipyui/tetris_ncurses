#include "tetris.hpp"
#include <cstdlib>
#include <cstring>
#include <ctime>


/////// iBlock stuff ///////

iBlock::iBlock() {
    std::srand(std::time(0));
    id = std::rand() % 7;
    set_block();
};

// Input is number 0-6, to determine kind of block.
iBlock::iBlock(short i) : id(i) { set_block(); };

void iBlock::set_block() {

    clear_grid();
    
	switch (id) {
		// I
        case 0:
            blocks.grid[0][0] = RED;
            blocks.grid[1][0] = RED;
            blocks.grid[2][0] = RED;
            blocks.grid[3][0] = RED;
        	break;
        // J
        case 1:
            blocks.grid[0][0] = GREEN;
            blocks.grid[1][0] = GREEN;
            blocks.grid[1][1] = GREEN;
            blocks.grid[1][2] = GREEN;
        	break;
        // L
        case 2:
            blocks.grid[0][2] = BLUE;
            blocks.grid[1][0] = BLUE;
            blocks.grid[1][1] = BLUE;
            blocks.grid[1][2] = BLUE;
        	break;
        // O
        case 3:
            blocks.grid[0][0] = YELLOW;
            blocks.grid[0][1] = YELLOW;
            blocks.grid[1][0] = YELLOW;
            blocks.grid[1][1] = YELLOW;
        	break;
        // S
        case 4:
            blocks.grid[0][1] = PURPLE;
            blocks.grid[0][2] = PURPLE;
            blocks.grid[1][0] = PURPLE;
            blocks.grid[1][1] = PURPLE;
        	break;
        // T
        case 5:
            blocks.grid[0][1] = ORANGE;
            blocks.grid[1][0] = ORANGE;
            blocks.grid[1][1] = ORANGE;
            blocks.grid[1][2] = ORANGE;
        	break;
        // Z
        case 6:
            blocks.grid[0][0] = LIGHT_BLUE;
            blocks.grid[0][1] = LIGHT_BLUE;
            blocks.grid[1][1] = LIGHT_BLUE;
            blocks.grid[1][2] = LIGHT_BLUE;
        	break;
        default:
        	break;
   }
}

void iBlock::rejustify() {
    while (empty_row(0))
        delete_row(0);
    while (empty_col(0))
        delete_col(0);
}

// All used by rejustify() //
bool iBlock::empty_row(short r) const {
    for (short j = 0; j < BLOCK_SIZE; ++j)
        if (blocks.grid[r][j] != EMPTY)
            return false;
    return true;
}

bool iBlock::empty_col(short c) const {
    for (short i = 0; i < BLOCK_SIZE; ++i)
        if (blocks.grid[i][c] != EMPTY)
            return false;
    return true;
}

void iBlock::delete_row(short r) {
    for (short i = r; i < BLOCK_SIZE - 1; ++i)
        for (short j = 0; j < BLOCK_SIZE; ++j)
            blocks.grid[i][j] = blocks.grid[i + 1][j];
    for (short j = 0; j < BLOCK_SIZE; ++j)
        blocks.grid[BLOCK_SIZE - 1][j] = EMPTY;
}

void iBlock::delete_col(short c) {
    for (short j = c; j < BLOCK_SIZE - 1; ++j)
        for (short i = 0; i < BLOCK_SIZE; ++i)
            blocks.grid[i][j] = blocks.grid[i][j + 1];
    for (short i = 0; i < BLOCK_SIZE; ++i)
        blocks.grid[i][BLOCK_SIZE - 1] = EMPTY;
}
// END all used by rejustify() //

void iBlock::clear_grid() {
	for (short i = 0; i < BLOCK_SIZE; ++i)
		for (short j = 0; j < BLOCK_SIZE; ++j)
			blocks.grid[i][j] = EMPTY;
}

grid_box iBlock::get_blocks() const {
    return blocks;
}

short iBlock::get_id() const {
    return id;
}

/////// END iBlock stuff ///////

/////// playField stuff ///////

playField::playField()
 : currentBlock(iBlock()), currentX(0), currentY(0) { build_well(); };

void playField::build_well() {
    for (short i = 0; i < WELL_HEIGHT; ++i) {
        gameGrid[i][0] = GREY;
        gameGrid[i][WELL_WIDTH - 1] = GREY;
    }
    for (short i = 0; i < WELL_WIDTH; ++i)
        gameGrid[WELL_HEIGHT - 1][i] = GREY;
}

// ---- Block movement ---- //
void playField::rotate(bool left) {
    iBlock rotated = iBlock(-1); // Produces empty iBlock
    rotated.id = currentBlock.id;

    // Initial rotation
    for (short i = 0; i < BLOCK_SIZE; ++i){ // rotates original onto copy
        for (short j = 0; j < BLOCK_SIZE; ++j) {
            if (left)
                rotated.blocks.grid[i][j] = currentBlock.blocks.grid[3-j][i];
            else
                rotated.blocks.grid[i][j] = currentBlock.blocks.grid[j][3-i];
        }
    }

    // Realign iBlock blocks with top-left corner of its grid.
    rotated.rejustify();

    // if this rotates it off the grid or onto another piece, we need to move it back
    for (short i = 0; i < BLOCK_SIZE; ++i)
        for (short j = 0; j < BLOCK_SIZE; ++j)
            if (rotated.blocks.grid[i][j] != EMPTY)
                return;

    std::memcpy(&currentBlock.blocks.grid, &rotated.blocks.grid, sizeof(color_block_t) * BLOCK_SIZE * BLOCK_SIZE);
}

void playField::move_left() {
    --currentX;
    if (check_collision())
        ++currentX;
}

void playField::move_right() {
    ++currentX;
    if (check_collision())
        --currentX;
}

bool playField::move_down() {
    ++currentY;
    if (check_collision()) {
        settle_block();
        return false;
    }
    return true;
}

void playField::hard_down() {
    while (move_down());
}

void playField::settle_block() {
    for (short i = 0; i < BLOCK_SIZE; ++i)
        for (short j = 0; j < BLOCK_SIZE; ++j)
            if (currentBlock.blocks.grid[i][j] != EMPTY)
                gameGrid[currentX + i][currentY + j - 1] = currentBlock.blocks.grid[i][j];
}
// ---- END Block movement ---- //

bool playField::check_collision() const {
    for (short j = BLOCK_SIZE - 1; j >= 0; --j)
        for (short i = 0; i < BLOCK_SIZE; ++i)
            if (currentBlock.blocks.grid[i][j] != EMPTY && gameGrid[currentX + i][currentY + j] != EMPTY)
                return true;
    return false;
}

bool playField::check_full_row(short r) const {
    for (short j = 1; j < WELL_WIDTH - 1; ++j)
        if (gameGrid[r][j] == EMPTY)
            return false;
    return true;
}

void playField::clear_row(short r) {
    for (short i = r; i > 0; --i)
        for (short j = 1; j < WELL_WIDTH - 1; ++j)
            gameGrid[i][j] = gameGrid[i - 1][j];
    for (short j = 1; j < WELL_WIDTH - 1; ++j)
        gameGrid[0][j] = EMPTY;
}

void playField::new_block() {
    currentBlock = iBlock();
    currentX = std::rand() % (WELL_WIDTH - 2) + 1;
    currentY = 0;
}

void playField::new_block(short nextBlockId) {
    currentBlock = iBlock(nextBlockId);
    currentX = std::rand() % (WELL_WIDTH - 2) + 1;
    currentY = 0;
}

color_block_t playField::block_at(short x, short y) const {
    return gameGrid[x][y];
}

iBlock playField::get_currentBlock() const {
    return currentBlock;
}

short playField::get_currentX() const {
    return currentX;
}

short playField::get_currentY() const {
    return currentY;
}

/////// END playField stuff ///////

///////// sidebar stuff ///////

sidebar::sidebar()
 : score(0), nextBlock(iBlock()) {};

int sidebar::bump_score() {
    return score += 10;
}

void sidebar::new_block() {
    nextBlock = iBlock();
}

int sidebar::get_score() const {
    return score;
}

iBlock sidebar::get_nextBlock() const {
    return nextBlock;
}

short sidebar::get_nextBlock_id() const {
    return nextBlock.get_id();
}

/////// END sidebar stuff ///////

/////// tetrisGame stuff ///////

tetrisGame::tetrisGame()
 : well(playField()), sbar(sidebar()) {};

void tetrisGame::rotate_left() {
    well.rotate(true);
}

void tetrisGame::rotate_right() {
    well.rotate(false);
}

void tetrisGame::move_left() {
    well.move_left();
}

void tetrisGame::move_right() {
    well.move_right();
}

bool tetrisGame::move_down() {
    return well.move_down();
}

void tetrisGame::hard_down() {
    well.hard_down();
}


void tetrisGame::clear_row(short r) {
    well.clear_row(r);
    sbar.bump_score();
}

void tetrisGame::new_block() {
    well.new_block(sbar.get_nextBlock_id());
    sbar.new_block();
}

/////// END tetrisGame stuff ///////
