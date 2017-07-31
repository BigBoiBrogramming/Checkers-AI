#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Board* board, Team team);
	friend ostream& operator<<(ostream& os, const King& k);
};

#endif
