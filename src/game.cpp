#include "game.h"

game::game() {

}

int game::init(int mode) {
	switch (mode) {
		case GAME_NOVICE:
			this -> gm = new game_mode( 10, 10, 10 );
			break;
		case GAME_NORMAL:
			this -> gm = new game_mode( 20, 20, 40 );
			break;
		case GAME_HARD:
			this -> gm = new game_mode( 30, 30, 99 );
			break;
		default:
			return 1;
	}

	if (this -> game_board) {
		delete(this -> game_board);
	}

	this -> game_board = new board(this -> gm -> getRows(), this -> gm -> getCols());
	this -> current_row = 0;
	this -> current_col = 0;
	this -> mines = this -> gm -> getMines();
	this -> initSeed();

	this -> fillMines();

	return 0;
}

void game::setPos(int row, int col) {
	this -> current_row = row;
	this -> current_col = col;
}

int game::click() {
	if (this -> game_board -> isMine(this -> current_row, this -> current_col)) {
		return 1;
	}

	this -> game_board -> open(this -> current_row, this -> current_col);
	return 0;
}

void game::flag() {
	this -> game_board -> setFlag( this -> current_row, this -> current_col );
}

int game::isWon() {
	if (this -> game_board -> isMinesFlagged()) {
		if (this -> game_board -> getFlagged() == this -> mines) {
			return 1;
		}
	}

	return 0;
}

void game::fillMines() {
	int cells = this -> game_board -> getRows() * this -> game_board -> getCols();
	for (int i = 0; i < this -> mines; i++) {
		int tmp_row, tmp_col;
		do {
			int r = rand();
			while (r == 0) { r = rand(); }
			r = r % cells;
			tmp_row = r / this -> game_board -> getCols();
			tmp_col = r % this -> game_board -> getCols();
		} while (this -> game_board -> isMine(tmp_row, tmp_col));
		printf("\n");

		this -> game_board -> setMine(tmp_row, tmp_col);
	}
}

int game::getRow() {
	return this -> current_row;
}

int game::getCol() {
	return this -> current_col;
}

void game::initSeed() {
	struct timeval t;
	gettimeofday(&t, NULL);
	int seed = (t.tv_sec/1000)+(t.tv_usec*1000);
	//seed = 909333011;
	srand(seed);
	printf("Started with seed %d\n", seed);
}

int game::getMines() {
	return this -> mines;
}

board * game::getBoard() {
	return this -> game_board;
}

game_mode::game_mode(int rows, int cols, int mines) {
	this -> rows = rows;
	this -> cols = cols;
	this -> mines = mines;
}

int game_mode::getRows() {
	return this -> rows;
}

int game_mode::getCols() {
	return this -> cols;
}

int game_mode::getMines() {
	return this -> mines;
}

game_mode::~game_mode() {

}
