#ifndef PIECE_H
#define PIECE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <stack>
#include "Team.h"
#include "Board.h"

class Board;
class Tile;

using namespace std;

class Piece {
public:
	Piece(Board* board, Team team, tuple<int,int> coordinates);
	~Piece();
	void move(tuple<int,int>& endTileCoord);
	set<stack<tuple<int,int> > > getAvailableMoves();
	set<stack<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int>& currentCoord);
	set<stack<tuple<int,int> > > getAvailableAttacks(tuple<int,int>& currentCoord);
	friend ostream& operator<<(ostream& os, const Piece& p);
	Team getTeam();
	void setTeam(Team& t);
	tuple<int,int> getCoordinates();

private:
	Board* board;
	Team team;
	tuple<int,int> coordinates;
};

#endif
