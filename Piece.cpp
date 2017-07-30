#include "Piece.h"

Piece::Piece(Board* board, Team team)
{
	this->board = board;
	this->team = team;
}

Piece::~Piece()
{
}

// print the piece
ostream& operator<<(ostream& os, const Piece& p)
{
	string color;
	if (p.team == Team::red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "n" << color;
	
	return os;
}

// returns a set containing stacks of moves
// a stack holds the coordinates (in sequence) that a piece traverses
set<stack<tuple<int,int> > > Piece::getAvailableMoves() 
{
	set<stack<tuple<int,int> > > availableMoves;
	
	// get single square moves
	set<stack<tuple<int,int> > > singleSquareMoves = getAvailableSingleSquareMoves(coordinates);
	
	// add single square moves to available moves
	for (auto singleSquareMove : singleSquareMoves) {
		availableMoves.insert(singleSquareMove);
	}
	
	// get attack moves
	set<stack<tuple<int,int> > > attackMoves = getAvailableAttacks(coordinates);
	
	// add single square moves to available moves
	for (auto attackMove : attackMoves) {
		availableMoves.insert(attackMove);
	}
	
	return availableMoves;
}


set<stack<tuple<int,int> > > Piece::getAvailableSingleSquareMoves(tuple<int,int> currentCoord)
{
	set<stack<tuple<int,int> > > availableSingleMoves;
	
	// intialize the forward direction and coordinate bound
	int moveDirection;
	int maxY;
	
	// if the team is red, move up 1 and bound is 7
	// otherwise, move down 1 and bound is 0
	if (team == Team::red) {
		moveDirection = 1;
		maxY = 7;
	} else {
		moveDirection = -1;
		maxY = 0;
	}
	
	// y coordinate of attempted diagonal moves
	// piece is not a king so can only move in one direction
	int attemptY = get<1>(coordinates) + moveDirection;
	
	// x coordinates of attempted diagonal moves
	int attempt1X = get<0>(coordinates) + 1;
	int attempt2X = get<0>(coordinates) - 1;
	
	// check if attack move is in bounds on the y-axis
	if (attemptY <= maxY) {
		// check if right side move is valid
		if (attempt1X <= 7 && !(board->tiles[attempt1X][attemptY]->hasPieceOnTile())) {
			
			stack<tuple<int,int> > move;
			move.push(make_tuple(attempt1X, attemptY));
			availableSingleMoves.insert(move);
		}
		// check if left side move is valid
		if (attempt2X >= 0 && !(board->tiles[attempt2X][attemptY]->hasPieceOnTile())) {
			
			stack<tuple<int,int> > move;
			move.push(make_tuple(attempt2X, attemptY));
			availableSingleMoves.insert(move);
		}
	}
	
	return availableSingleMoves;
}

set<stack<tuple<int,int> > > Piece::getAvailableAttacks(tuple<int,int> currentCoord)
{
	// a set containing coordinates of the first moves in leap chains
	set<tuple<int,int> > possiblePathStarters;
	
	// a set of attack chains that will eventually be returned
	set<stack<tuple<int,int> > > possibleAttackChains;
	
	// intialize the forward direction and coordinate bound
	int moveDirection;
	int maxY;
	
	// if the team is red, move up 2 and bound is 7
	// otherwise, move down 2 and bound is 0
	if (team == Team::red) {
		moveDirection = 2;
		maxY = 7;
		
	} else {
		moveDirection = -2;
		maxY = 0;
	}
	
	// y coordinate of attempted attacks (position after jumping)
	// piece is not a king so can only move in one direction
	int attemptY = get<1>(currentCoord) + moveDirection;
	
	// x coordinates of attempted attacks (position after jumping)
	int attempt1X = get<0>(currentCoord) + 2;
	int attempt2X = get<0>(currentCoord) - 2;
	
	// check if attack move is in bounds on the y-axis
	if (attemptY <= maxY) {
		// check if right side attack move is valid
		if ( attempt1X <= 7 
		&& !(board->tiles[attempt1X][attemptY]->hasPieceOnTile()) 
		&& (board->tiles[attempt1X - (moveDirection/2)][attemptY - (moveDirection/2)]->getTeamOfPieceOnTile() != team)) 
		{
			possiblePathStarters.insert(make_tuple(attempt1X, attemptY));
		}
		// check if left side attack move is valid
		if ( attempt2X >= 0
		&& !(board->tiles[attempt2X][attemptY]->hasPieceOnTile())  
		&& (board->tiles[attempt2X - (moveDirection/2)][attemptY - (moveDirection/2)]->getTeamOfPieceOnTile() != team))
		{
			possiblePathStarters.insert(make_tuple(attempt2X, attemptY));
		}
	}
	
	// go through each coordinate for a path starter
	for(auto firstStepCoord : possiblePathStarters) {
		
		// recursive call to create chains of steps after moving to firstStepCoord
		set<stack<tuple<int,int> > > chainsAfterFirstStep = getAvailableAttacks(firstStepCoord);
		
		// go through chains and add on the first step
		for(auto chain: chainsAfterFirstStep) {
			chain.push(firstStepCoord);
			possibleAttackChains.insert(chain);
		}
		
		// add on smallest chain, our first step, to attack chains
		stack<tuple<int,int> > smallestChain;
		smallestChain.push(firstStepCoord);
		possibleAttackChains.insert(smallestChain);
	}
	
	return possibleAttackChains;
}

void Piece::move(tuple<int,int> endTileCoords)
{
	if (!(board->tiles[get<0>(endTileCoords)][get<1>(endTileCoords)]->hasPieceOnTile())) {
		board->tiles[get<0>(coordinates)][get<1>(coordinates)]->setPiece(NULL);
		board->tiles[get<0>(endTileCoords)][get<1>(endTileCoords)]->setPiece(this);
		coordinates = endTileCoords;
	}
	else {
		cerr << "there is already a tile here";
	}
}
