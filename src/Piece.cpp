#include "Piece.h"

Piece::Piece(Board* board, Team team, tuple<int,int> coordinate)
{
	this->board = board;
	this->team = team;
	this->coordinate = coordinate;
}

Piece::~Piece()
{
}

// move the tile to the specified coordinate
void Piece::move(tuple<int,int> endTileCoord)
{
	if (board->getTiles()[get<1>(endTileCoord)][get<0>(endTileCoord)]->hasPieceOnTile()) {
		AlreadyHasPieceException e = AlreadyHasPieceException(get<0>(coordinate), get<1>(coordinate));
		cerr << e.what();
		exit(1);
	}
	
	board->getTiles()[get<1>(coordinate)][get<0>(coordinate)]->setPiece(NULL);
	board->getTiles()[get<1>(endTileCoord)][get<0>(endTileCoord)]->setPiece(this);
	coordinate = endTileCoord;
}

// returns a set containing deque of moves
// a deque holds the coordinates (in sequence) that a piece traverses
set<deque<tuple<int,int> > > Piece::getAvailableMoves() 
{
	// the set of moves that gets returned
	set<deque<tuple<int,int> > > availableMoves;
	
	// get single square moves
	set<deque<tuple<int,int> > > singleSquareMoves = getAvailableSingleSquareMoves(coordinate);
	
	// add single square moves to available moves
	for (auto singleSquareMove : singleSquareMoves) {
		availableMoves.insert(singleSquareMove);
	}
	
	// get attack moves
	set<deque<tuple<int,int> > > attackMoves = getAvailableAttacks(coordinate);
	
	// add single square moves to available moves
	for (auto attackMove : attackMoves) {
		availableMoves.insert(attackMove);
	}
	
	return availableMoves;
}

// returns the set of single square moves
set<deque<tuple<int,int> > > Piece::getAvailableSingleSquareMoves(tuple<int,int>& currentCoord)
{
	// the set of single moves that gets returned
	set<deque<tuple<int,int> > > availableSingleMoves;
	
	// intialize the forward direction and coordinate bound
	int moveDirection;
	int maxY;
	
	// set directions for movement based on team
	if (team == red) {
		moveDirection = 1;
		maxY = 7;
	} else {
		moveDirection = -1;
		maxY = 0;
	}
	
	// y coordinate of attempted diagonal moves
	// piece is not a king so can only move in one direction
	int attemptY = get<1>(coordinate) + moveDirection;
	
	// x coordinates of attempted diagonal moves
	int attempt1X = get<0>(coordinate) + 1;
	int attempt2X = get<0>(coordinate) - 1;
	
	// check if attack move is in bounds on the y-axis
	if ((team == red && attemptY <= maxY) || (team == black && attemptY >= maxY)) {
		// check if right side move is valid
		if (attempt1X <= 7 && !(board->getTiles()[attemptY][attempt1X]->hasPieceOnTile())) {
			// add the right side move to the set of available moves
			deque<tuple<int,int> > move;
			move.push_front(make_tuple(attempt1X, attemptY));
			availableSingleMoves.insert(move);
		}
		// check if left side move is valid
		if (attempt2X >= 0 && !(board->getTiles()[attemptY][attempt2X]->hasPieceOnTile())) {
			// add the left side move to the set of available moves
			deque<tuple<int,int> > move;
			move.push_front(make_tuple(attempt2X, attemptY));
			availableSingleMoves.insert(move);
		}
	}
	
	return availableSingleMoves;
}

// returns the set of attack moves
set<deque<tuple<int,int> > > Piece::getAvailableAttacks(tuple<int,int>& currentCoord)
{
	// the set of attack chains that gets returned
	set<deque<tuple<int,int> > > possibleAttackChains;
		
	// a set containing coordinates of the first moves in leap chains
	set<tuple<int,int> > possiblePathStarters;
	
	// intialize the forward direction and coordinate bound
	int moveDirection;
	int maxY;
	
	// if the team is red, move up 2 and bound is 7
	// otherwise, move down 2 and bound is 0
	if (team == red) {
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
	if ((team == red && attemptY <= maxY) || (team == black && attemptY >= maxY)) {
		// check if right side attack move is valid
		if ((attempt1X <= 7)
		&& !(board->getTiles()[attemptY][attempt1X]->hasPieceOnTile())
		&& (board->getTiles()[attemptY-(moveDirection/2)][attempt1X-1]->hasPieceOnTile())
		&& (board->getTiles()[attemptY-(moveDirection/2)][attempt1X-1]->getPiece()->getTeam() != team)) {
			// add the right side attack coordinate to the set of possible path starters
			possiblePathStarters.insert(make_tuple(attempt1X, attemptY));
		}
		// check if left side attack move is valid
		if ((attempt2X >= 0)
		&& !(board->getTiles()[attemptY][attempt2X]->hasPieceOnTile())
		&& (board->getTiles()[attemptY-(moveDirection/2)][attempt2X+1]->hasPieceOnTile())
		&& (board->getTiles()[attemptY-(moveDirection/2)][attempt2X+1]->getPiece()->getTeam() != team)) {
			// add the left side attack coordinate to the set of possible path starters
			possiblePathStarters.insert(make_tuple(attempt2X, attemptY));
		}
	}
	
	// iterate through the coordinates of path starters
	for(auto firstStepCoord : possiblePathStarters) {
		// recursive call to generate all chains of steps after moving to the first step
		set<deque<tuple<int,int> > > chainsAfterFirstStep = getAvailableAttacks(firstStepCoord);
		
		// iterate through chains and add the first step onto the attack chains
		for(auto chain : chainsAfterFirstStep) {
			chain.push_front(firstStepCoord);
			possibleAttackChains.insert(chain);
		}
		
		// create the smallest possible chain that consists of only the first step
		deque<tuple<int,int> > smallestChain;
		smallestChain.push_front(firstStepCoord);
		possibleAttackChains.insert(smallestChain);
	}
	
	return possibleAttackChains;
}

// print the piece
ostream& operator<<(ostream& os, const Piece& p)
{
	string color;
	if (p.team == red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "n" << color;
	
	return os;
}

// return the team
Team Piece::getTeam()
{
	return team;
}

// set the team
void Piece::setTeam(Team& t)
{
	team = t;
}

// return the coordinates
tuple<int,int> Piece::getCoordinate()
{
	return coordinate;
}
