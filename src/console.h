#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include <panel.h>
#include "board.h"

class console {
	public:
		console();
		void printBoard(board * bptr);
		void showQuit();
		void setCursor(int row, int col);
		int readKey();
		int quit();
		int requestNewGame();
		void gameOver();
		void debug(std::string str);
		~console();
	private:
		PANEL * quit_panel;
		WINDOW * quit_window;
		WINDOW * main_window;
		WINDOW * debug_window;
		WINDOW * new_game_window;
		PANEL * new_game_panel;
		WINDOW * game_over_window;
		PANEL * game_over_panel;
		void clearWindow(WINDOW * w);
		void showPanel(PANEL * p);
		void hidePanel(PANEL * p);
		void initGameOverDialog();
		void initNewGameDialog();
		void initDebugWindow();
		void initMainWindow();
		void initQuitDialog();
};

#endif
