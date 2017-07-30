#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Board*, Team);
	friend ostream& operator<<(ostream&, const King&);
};

#endif
