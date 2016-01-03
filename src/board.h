#ifndef BOARD_H
#define BOARD_H 1

#include <stdio.h>
#include <stdlib.h>

class board {
	public:
		board(int rows, int cols);
		void setMine(int row, int col);
		int getRows();
		int getCols();
		int isMine(int row, int col);
		char getPoint(int row, int col);
		void open(int row, int col);
		void setFlag(int row, int col);
		int isMinesFlagged();
		int getFlagged();
		int getFlaggedMines();
		~board();

	protected:
		int rows;
		int cols;
		int flagged;
		int flagged_mines;
		char ** b;
		static const int flag_t = 32;
		static const int mine_t = 10;
		static const int offset_t = 16;

    int comparePoints(int row_1, int col_1, int row_2, int col_2);
    int isVisible(int point);
};

#endif
