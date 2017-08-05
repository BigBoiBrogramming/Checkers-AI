#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Team.h"

using namespace std;

class Player {
public:
	Player();
	Player(int number, string n, Team t);
	~Player();
	int getPlayerNumber();
	void setPlayerNumber(int& num);
	string getName();
	void setName(string& name);
	Team getTeam();
	int getPiecesRemaining();
	void decrementPiecesRemaining();
	
private:
	int playerNumber;
	string name;
	Team team;
	int piecesRemaining;
};

#endif
