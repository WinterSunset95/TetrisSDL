#include "structs.h"
#include "blocks.h"

int squareBlock(Cell *center, Cell *block) {
	if (center->filled == 0 || center->center == 0) {
		return 0;
	}
	int x = center->x;
	int y = center->y;

	block[0] = (Cell){x, y, 1, 1};
	block[1] = (Cell){x+1, y, 1, 1};
	block[2] = (Cell){x, y+1, 1, 1};
	block[3] = (Cell){x+1, y+1, 1, 1};

	//rotation = center->rotation;
	return 0;
}
