#ifndef GAME_H
#define GAME_H 1

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include "board.h"

#define GAME_NOVICE 0
#define GAME_NORMAL 1
#define GAME_HARD 2

class game_mode {
	public:
		game_mode(int rows, int cols, int mines);
		int getRows();
		int getCols();
		int getMines();
		~game_mode();
	private:
		int rows;
		int cols;
		int mines;
};

class game {
	public:
		game();
		int init(int mode);
		board * getBoard();
		int click();
		int getRow();
		int getCol();
		void setPos(int row, int col);
		void flag();
		int isWon();
		int getMines();
		~game();
	private:
		int mines;
		void initSeed();
		void fillMines();

		board * game_board;
		game_mode * gm;
		int current_row;
		int current_col;
};

#endif
