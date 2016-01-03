#include "console.h"

console::console() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	this -> initQuitDialog();
	this -> initGameOverDialog();
	this -> initMainWindow();
	this -> initDebugWindow();
	this -> initNewGameDialog();
}

void console::printBoard(board * bptr) {
	this -> hidePanel(this -> game_over_panel);
	this -> clearWindow(this -> main_window);
	wmove(this -> main_window, 1, 1);
	for (int i = 0; i < bptr -> getRows(); i++) {
		for (int j = 0; j < bptr -> getCols(); j++) {
			char p = bptr -> getPoint(i, j);

			if (p == '0') {
				p = ' ';
			}

			wprintw(this -> main_window, "%c ", p);
		}
		wmove(this -> main_window, i + 2, 1);
	}
	wrefresh(this -> main_window);
}

void console::initGameOverDialog() {
	this -> game_over_window = newwin(5, 15, 5, 5);
	this -> game_over_panel = new_panel(this -> game_over_window);
	hide_panel(this -> game_over_panel);
	update_panels();
	mvwprintw(this -> game_over_window, 2, 2, "GAME OVER");
	box(this -> game_over_window, 0, 0);
	doupdate();
}

void console::gameOver() {
	this -> showPanel(this -> game_over_panel);
}

void console::initNewGameDialog() {
	this -> new_game_window = newwin(7, 40, 5, 5);
	this -> new_game_panel = new_panel(this -> new_game_window);
	hide_panel(this -> new_game_panel);
	update_panels();
	mvwprintw(this -> new_game_window, 2, 2, "Novice");
	mvwprintw(this -> new_game_window, 3, 2, "Normal");
	mvwprintw(this -> new_game_window, 4, 2, "Hard");
	box(this -> new_game_window, 0, 0);
	doupdate();
}

void console::initQuitDialog() {
	this -> quit_window = newwin(5, 40, 5, 5);
	this -> quit_panel = new_panel(this -> quit_window);
	hide_panel(this -> quit_panel);
	update_panels();
	mvwprintw(this -> quit_window, 2, 2, "Do you want really quit (Y/n)?");
	box(this -> quit_window, 0, 0);
	doupdate();
}

int console::quit() {
	int exit = 0;
	this -> showPanel(this -> quit_panel);

	while (int ch = getch()) {
		switch (ch) {
			case 10:
			case 'y':
			case 'Y':
				return 1;
			case 'n':
			case 'N':
				exit = 1;
				break;
		}

		if (exit) {
			break;
		}
	}

	this -> hidePanel(this -> quit_panel);
	return 0;
}

void console::setCursor(int row, int col) {
	wmove(this -> main_window, (row + 1), (col * 2) + 1);
	wrefresh(this -> main_window);
}

void console::debug(std::string str) {
	int row = getcury(this -> debug_window);
	row++;
	if (row > 3) {
		this -> clearWindow(this -> debug_window);
		row = 1;
	}

	mvwprintw(this -> debug_window, row, 1, str.c_str());
	wrefresh(this -> debug_window);
}

void console::clearWindow(WINDOW * w) {
	wclear(w);
	box(w, 0, 0);
	wrefresh(w);
}

void console::showPanel(PANEL * p) {
	show_panel(p);
	update_panels();
	doupdate();
}

void console::hidePanel(PANEL * p) {
	hide_panel(p);
	update_panels();
	doupdate();
}

void console::initMainWindow() {
	this -> main_window = newwin(34, 78, 0, 0);
	box(this -> main_window, 0, 0);
	wrefresh(this -> main_window);
}

void console::initDebugWindow() {
	this -> debug_window = newwin(5, 78, 34, 0);
	box(this -> debug_window, 0, 0);
	wrefresh(this -> debug_window);
}

int console::readKey() {
	int ch = 0;
	while (ch = getch()) {
		switch (ch) {
			case 'q':
				if (this -> quit()) {
					return -1;
				}
				break;
			default:
				return ch;
		}
	}

	return ch;
}

int console::requestNewGame() {
	this -> showPanel(this -> new_game_panel);
	int row = 2, col = 1;
	wmove(this -> new_game_window, row, col);
	wrefresh(this -> new_game_window);
	while (int ch = getch()) {
		switch (ch) {
			case KEY_UP:
				row--;
				if (row < 2) {
					row = 4;
				}
				break;
			case KEY_DOWN:
				row++;
				if (row > 4) {
					row = 2;
				}
				break;
			case 27:
				row = 1;
			case 10:
				ch = -1;
				break;
		}

		if (ch == -1) {
			break;
		}

		wmove(this -> new_game_window, row, col);
		wrefresh(this -> new_game_window);
	}

	this -> hidePanel(this -> new_game_panel);
	return row - 2;
}

console::~console() {
	endwin();
}
