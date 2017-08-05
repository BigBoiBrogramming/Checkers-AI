#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Board.h"

using namespace std;

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

string inputName()
{
	cout << "Enter the player's name: ";
	cin.ignore();
	string name;
	getline(cin, name);
	return name;
}

void inputCoordinates(int& x, int& y, Board& board, Team team)
{
	cin >> x >> y;

	// repeat until the user enters valid coordinates
	while(!cin || x < 0 || x > 7 || y < 0 || y > 7) {
		cout << "Please enter valid integers separated by a space (x y): ";
		cin.clear();
		cin.ignore();
		cin >> x >> y;
	}
	
	// check if coordinates point to a piece on the board
	// x and y are flipped because row column indexing is the inverse of cartesian indexing
	Piece* piece;
	if (board.getTiles()[y][x]->hasPieceOnTile()) {
		piece = board.getTiles()[y][x]->getPiece();
	}
	
	// check if the tile is empty or if the piece is the wrong team
	if (piece == NULL || piece->getTeam() != team) {
		cout << "The space you selected does not contain a friendly piece." << endl;
		cin.clear();
		cin.ignore();
		
		// recursively call the function until valid coordinates are entered
		inputCoordinates(x, y, board, team);
	}
}

#endif
