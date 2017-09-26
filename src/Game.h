#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "King.h"
#include <map>

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
