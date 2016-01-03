#include "board.h"

board::board(int rows, int cols) {
	this -> rows = rows;
	this -> cols = cols;
	this -> flagged = 0;
	this -> flagged_mines = 0;

	// Если нужна производительность, можно использовать malloc вместо calloc,
	// но тогда надо самому следить за мусором
	this -> b = (char**)calloc(this -> rows, sizeof(char*));
	for (int i = 0; i < this -> rows; i++) {
		this -> b[i] = (char*)calloc(this -> cols, sizeof(char));
	}
}

int board::isMine(int row, int col) {
	if ((this -> b[row][col] & this -> mine_t) == this -> mine_t) {
		return 1;
	}

	return 0;
}

void board::setMine(int mine_row, int mine_col) {
	this -> b[mine_row][mine_col] = this -> mine_t;
	for (int i = mine_row - 1; i < mine_row + 2; i++) {
		if (i < 0 || i > (this -> rows - 1)) {
			continue;
		}

		for (int j = mine_col - 1; j < mine_col + 2; j++) {
			if (j < 0 || j > (this -> cols - 1)) {
				continue;
			}

			// Skip mines
			if (this -> b[i][j] == this -> mine_t) {
				continue;
			}

			// Init trash memory
			if (this -> b[i][j] < 0 || this -> b[i][j] > 10) {
				this -> b[i][j] = 0;
			}

			this -> b[i][j]++;
		}
	}
}

int board::isMinesFlagged() {
	if (this -> flagged == this -> flagged_mines) {
		return 1;
	}

	return 0;
}

int board::getFlagged() {
	return this -> flagged;
}

int board::getFlaggedMines() {
	return this -> flagged_mines;
}

void board::setFlag(int row, int col) {
	if (row < 0 || row > this -> rows || col < 0 || col > this -> cols) {
		exit(1);
	}

	this -> b[row][col] ^= this -> flag_t;
	if (this -> b[row][col] & this -> flag_t) {
		if (this -> isMine(row, col)) {
			this -> flagged_mines++;
		}

		this -> flagged++;
	}
	else {
		if (this -> isMine(row, col)) {
			this -> flagged_mines--;
		}

		this -> flagged--;
	}
}

int board::getRows() {
	return this -> rows;
}

int board::getCols() {
	return this -> cols;
}

void board::open(int row, int col) {
	int num = 0;

	int point = this -> b[row][col];
	int flagged = 0;
	if (this -> isVisible(this -> b[row][col])) {
		point ^= this -> offset_t;
		flagged = 1;
	}

	if (point > 0 && point < 10) {
		num = 1;
	}

	for (int i = row - 1; i < row + 2; i++) {
		if (i < 0 || i > (this -> rows - 1)) {
			continue;
		}

		for (int j = col - 1; j < col + 2; j++) {
			if (j < 0 || j > (this -> cols - 1)) {
				continue;
			}

			if (this -> b[i][j] == 0 && ! this -> comparePoints(i, j, row, col)) {
				this -> open(i, j);
			}

			if (num && this -> b[i][j] > 0 && this -> b[i][j] < 10) {
				continue;
			}

			if (this -> b [i][j] == this -> mine_t) {
				continue;
			}
		
			if (!this -> isVisible(this -> b[i][j])) {
				this -> b[i][j] |= this -> offset_t;
			}
		}
	}

	if (!flagged || point == this -> mine_t) {
		this -> b[row][col] |= this -> offset_t;
	}
}

int board::isVisible(int point) {
	if (point & this -> offset_t) {
		return 1;
	}

	return 0;
}

int board::comparePoints(int row_1, int col_1, int row_2, int col_2) {
	if (row_1 == row_2 && col_1 == col_2) {
		return 1;
	}

	return 0;
}

char board::getPoint(int row, int col) {
	if (row < 0 || row > this -> rows) {
		return -1;
	}

	if (col < 0 || col > this -> cols) {
		return -1;
	}

	if (this -> b[row][col] & this -> flag_t) {
		return 'F';
	}

	int tmp = this -> b[row][col] ^ this -> offset_t;
	if (tmp >= 0 && tmp < 10) {
		return (tmp + '0');
	}

	return '_';
}

board::~board() {
	for (int i = 0; i < this -> rows; i++) {
		delete(this -> b[i]);
	}

	delete(this->b);
}
