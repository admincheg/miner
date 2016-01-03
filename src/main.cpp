#include "main.h"

int main(int argc, char ** argv) {
	int debug = 0;
	int play = 0;
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-d")) {
			debug = 1;
		}
	}

	game * g = new game();

	if (debug) {
		g -> init(GAME_HARD);
		g -> setPos(1,2);
		g -> click();
		dbg * d = new dbg();
		d -> printBoard(g -> getBoard());
		return 0;
	}

	console * c = new console();

	int exit = 0;
	int row = 0;
	int col = 0;
	int ng = -1;
	board * b = NULL;
	while (int ch = c -> readKey()) {
		switch (ch) {
			case -1:
				exit = 1;
				break;
			case 'n':
				ng = c -> requestNewGame();
				if (ng >= 0) {
					g -> init(ng);
					c -> printBoard(g -> getBoard());
					c -> setCursor(g -> getRow(), g -> getCol());
					play = 1;
				}
				break;
			case KEY_UP:
				if (!play) {
					break;
				}

				row = g -> getRow();
				if (row > 0) {
					row--;
					g -> setPos(row, g -> getCol());
				}
				c -> setCursor(g -> getRow(), g -> getCol());
				break;
			case KEY_DOWN:
				if (!play) {
					break;
				}

				b = g -> getBoard();
				row = g -> getRow();
				if (row < (b -> getRows() - 1)) {
					row++;
					g -> setPos(row, g -> getCol());
				}
				c -> setCursor(g -> getRow(), g -> getCol());
				break;
			case KEY_LEFT:
				if (!play) {
					break;
				}

				col = g -> getCol();
				if (col > 0) {
					col--;
					g -> setPos(g -> getRow(), col);
				}
				c -> setCursor(g -> getRow(), g -> getCol());
				break;
			case KEY_RIGHT:
				if (!play) {
					break;
				}
				b = g -> getBoard();
				col = g -> getCol();
				if (col < (b -> getCols() - 1)) {
					col++;
					g -> setPos(g -> getRow(), col);
				}
				c -> setCursor(g -> getRow(), g -> getCol());
				break;
			case ' ':
				if (!play) {
					break;
				}

				if (g -> click()) {
					c -> debug("MINE!");
					c -> gameOver();
					play = 0;
				}
				else {
					c -> printBoard(g -> getBoard());
					c -> setCursor(g -> getRow(), g -> getCol());
				}
				break;
			case 'z':
				if (!play) {
					break;
				}

				g -> flag();
				c -> printBoard(g -> getBoard());
				c -> setCursor(g -> getRow(), g -> getCol());
				break;
		}

		if (g && g -> isWon()) {
			play = 0;
			c -> debug("You won!");
			break;
		}

		if (exit) {
			break;
		}
	}

	delete(c);
	//g -> setPos(1,1);
	//g -> click();
	return 0;
}
