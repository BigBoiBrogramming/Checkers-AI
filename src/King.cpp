#include "King.h"

King::King(Board* board, Team team, tuple<int,int> coordinates) : Piece (board, team, coordinates)
{
}

// returns a set containing deque of moves
// a deque holds the coordinates (in sequence) that a piece traverses
set<deque<tuple<int,int> > > King::getAvailableMoves() 
{
	// the set of moves that gets returned
	set<deque<tuple<int,int> > > availableMoves;
	
	// get single square moves
	set<deque<tuple<int,int> > > singleSquareMoves = getAvailableSingleSquareMoves(coordinates);
	
	// add single square moves to available moves
	for (auto singleSquareMove : singleSquareMoves) {
		// add on the starting coordinates to each move
		singleSquareMove.push_front(coordinates);
		availableMoves.insert(singleSquareMove);
	}
	
	// create the empty set holding coordinates of jumped pieces
	set<tuple<int,int> > jumpedCoordinates;
	
	// get attack moves
	set<deque<tuple<int,int> > > attackMoves = getAvailableAttacks(coordinates, jumpedCoordinates);
	
	// add single square moves to available moves
	for (auto attackMove : attackMoves) {
		// add on the starting coordinates to each move
		attackMove.push_front(coordinates);
		availableMoves.insert(attackMove);
	}
	
	return availableMoves;
}

// returns the set of single square moves
set<deque<tuple<int,int> > > King::getAvailableSingleSquareMoves(tuple<int,int>& currentCoord)
{
	// the set of single moves that gets returned
	set<deque<tuple<int,int> > > availableSingleMoves;
	
	// iterate through both possible directions
	for (int i = 0; i < 2; i++) {
		// intialize the forward direction and coordinate bound
		int moveDirection;
		
		// for one direction, move up 1 and bound is 7
		// for the other, move down 1 and bound is 0
		if (i == 0) {
			moveDirection = 1;
		} else {
			moveDirection = -1;
		}
		
		// y coordinate of attempted diagonal moves
		int attemptY = get<1>(coordinates) + moveDirection;
		
		// x coordinate of attempted diagonal moves
		int attempt1X = get<0>(coordinates) + 1;
		int attempt2X = get<0>(coordinates) - 1;
		
		// check if attack move is in bounds on the y-axis
		if ((attemptY >= 0) && (attemptY <= 7)) {
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
	}
	
	return availableSingleMoves;
}

// returns the set of attack moves
set<deque<tuple<int,int> > > King::getAvailableAttacks(tuple<int,int>& currentCoord, set<tuple<int,int> >& jumpedCoordinates)
{
	// the set of attack chains that gets returned
	set<deque<tuple<int,int> > > possibleAttackChains;
		
	// a set containing coordinates of the first moves in leap chains
	set<tuple<int,int> > possiblePathStarters;
	
	// intialize the forward direction and coordinate bound
	int moveDirection;
	int maxY;
	
	// iterate through each move direction
	for (int i = 0; i < 2; i++) {
		
		// when moving up, move up 2 and bound is 7
		// when moving down, move down 2 and bound is 0
		if (i == 0) {
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
		if ((i == 0 && attemptY <= maxY) || (i == 1 && attemptY >= maxY)) {
			// check if right side attack move is valid
			if ((attempt1X <= 7)
			&& !(board->getTiles()[attemptY][attempt1X]->hasPieceOnTile())
			&& (board->getTiles()[attemptY-(moveDirection/2)][attempt1X-1]->hasPieceOnTile())
			&& (board->getTiles()[attemptY-(moveDirection/2)][attempt1X-1]->getPiece()->getTeam() != team)
			&& !(pieceAlreadyJumped(jumpedCoordinates, make_pair(attemptY-(moveDirection/2), attempt1X-1)))) {
				// add the right side attack coordinates to the set of possible path starters
				possiblePathStarters.insert(make_tuple(attempt1X, attemptY));
				
				// add the jumped piece to the set of jumped coordinates
				jumpedCoordinates.insert(make_pair(attemptY-(moveDirection/2), attempt1X-1));
			}
			// check if left side attack move is valid
			if ((attempt2X >= 0)
			&& !(board->getTiles()[attemptY][attempt2X]->hasPieceOnTile())
			&& (board->getTiles()[attemptY-(moveDirection/2)][attempt2X+1]->hasPieceOnTile())
			&& (board->getTiles()[attemptY-(moveDirection/2)][attempt2X+1]->getPiece()->getTeam() != team)
			&& !(pieceAlreadyJumped(jumpedCoordinates, make_pair(attemptY-(moveDirection/2), attempt2X+1)))) {
				// add the left side attack coordinates to the set of possible path starters
				possiblePathStarters.insert(make_tuple(attempt2X, attemptY));
				
				// add the jumped piece to the set of jumped coordinates
				jumpedCoordinates.insert(make_pair(attemptY-(moveDirection/2), attempt2X+1));
			}
		}
		
		// iterate through the coordinates of path starters
		for(auto firstStepCoord : possiblePathStarters) {
			// recursive call to generate all chains of steps after moving to the first step
			set<deque<tuple<int,int> > > chainsAfterFirstStep = getAvailableAttacks(firstStepCoord, jumpedCoordinates);
			
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
	}
		
	return possibleAttackChains;
}

// check if a piece is already jumped
bool King::pieceAlreadyJumped(set<tuple<int,int> >& jumpedCoordinates, pair<int,int> checkCoordinate) const
{
	set<tuple<int,int> >::iterator it = jumpedCoordinates.find(checkCoordinate);
	if (it != jumpedCoordinates.end()) {
		// piece is already jumped
		return true;
	} else {
		// piece has not been jumped
		return false;
	}
}

// print the piece
void King::printMyself() const
{
	string color;
	if (team == red) {
		color = "R";
	} else {
		color = "B";
	}
	
	cout << "k" << color;
}
