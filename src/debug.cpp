#include "debug.h"

dbg::dbg() {

}

void dbg::printBoard(board * b) {
	for (int i = 0; i < b -> getRows() - 1; i++) {
		for (int j = 0; j < b -> getCols() - 1; j++) {
			printf("%c ", b -> getPoint(i, j));
		}
		printf("\n");
	}
}
