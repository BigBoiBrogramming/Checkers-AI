#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "King.h"
#include "Player.h"

using namespace std;

// retrieve user input for player type
bool inputPlayerType(int playerNumber)
{
	string answer;
	cout << "Would you like player " << playerNumber << " to be AI (y/n): ";
	while (answer != "y" && answer != "n") {
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(),::tolower);
		if (answer != "y" && answer != "n") {
			cout << "Enter either 'y' or 'n': ";
		}
	}
	
	return answer == "y";
}

// retrieve user input for player name
string inputName()
{
	cout << "Enter the player's name: ";
	cin.ignore();
	string name;
	getline(cin, name);
	return name;
}

// retrieve user input for piece coordinates
void inputCoordinates(int& x, int& y, Board& board, Team team)
{
	cin >> x >> y;

	// repeat until the user enters valid coordinates
	while(!cin || x < 0 || x > 7 || y < 0 || y > 7) {
		cout << "Please enter valid coordinates separated by a space (x y): ";
		cin.clear();
		cin.ignore(200, '\n');
		cin >> x >> y;
	}
	
	// check if coordinates point to a piece on the board
	// x and y are flipped because row column indexing is the inverse of cartesian indexing
	Piece* piece = NULL;
	if (board.getTiles()[y][x]->hasPieceOnTile()) {
		piece = board.getTiles()[y][x]->getPiece();
	}
	
	// check if the tile is empty or if the piece is the wrong team
	if (piece == NULL || piece->getTeam() != team) {
		cout << "The coordinates you selected do not contain a friendly piece." << endl;
		cin.clear();
		cin.ignore();
		
		// recursively call the function until valid coordinates are entered
		inputCoordinates(x, y, board, team);
	}
}

// select a piece and return its available moves
set<deque<tuple<int,int> > > selectPieceAndGetMoves(Board& board, Player*& player)
{
	set<deque<tuple<int,int> > > availableMoves;
	
	// keep getting available moves until a valid choice is selected
	while (availableMoves.size() == 0) {
		int x, y;
		
		// get the coordinates of the piece from the user
		inputCoordinates(x, y, board, player->getTeam());
		
		// retrieve the available moves
		availableMoves = board.getTiles()[y][x]->getPiece()->getAvailableMoves();
		
		// try again if no moves were available
		if (availableMoves.size() == 0) {
			cout << "Selected piece has no available moves, please try again." << endl;
		}
	}
	
	return availableMoves;
}

// display all the available moves and return them in a map
map<int, deque<tuple<int,int> > > displayMovesAndReturnMap(set<deque<tuple<int,int> > >& availableMoves)
{
	// initialize a map to hold moves with numbered keys
	map<int, deque<tuple<int,int> > > moveMap;
	
	cout << "Select move:" << endl;
	int moveCounter = 1;
	
	cout << "0: Select a different piece." << endl;
	
	// iterate through each move set
	for (auto deque : availableMoves) {
		cout << moveCounter << ": ";
		for (auto move : deque) {
			if (move != deque.front()) {
				cout << "->(" << get<0>(move) << ", " << get<1>(move) << ")";
			}
		}
		cout << endl;
		
		// insert the move into the map
		moveMap.insert(make_pair(moveCounter, deque));
		
		moveCounter++;
	}
	
	return moveMap;
}

// retrieve user input for move number
int getMoveNumber(int numMoves)
{
	int moveNumber;
	cin >> moveNumber;
	
	// repeat until the user enters valid coordinates
	while(!cin || moveNumber < 0 || moveNumber > numMoves) {
		cout << "Please enter a valid move number: ";
		cin.clear();
		cin.ignore();
		cin >> moveNumber;
	}
	
	return moveNumber;
}

// update a piece at the given coordinates to a king if needed
void updateToKingIfNeeded(Board& board, tuple<int,int>& endCoordinates, Team team)
{
	int x = get<0>(endCoordinates);
	int y = get<1>(endCoordinates);
	
	// check if piece is not already a king
	if (King* kingCheck = dynamic_cast<King*>(board.getTiles()[y][x]->getPiece())) {
		return;
	}
	
	// change the piece to a king if it has reached the end of the board
	if ((team == red && y == 7) || (team == black && y == 0)) {
		board.getTiles()[y][x]->removePieceFromTile();
		board.getTiles()[y][x]->setPiece(new King(&board, team, endCoordinates));
	}
}

#endif
