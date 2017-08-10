#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Team.h"

using namespace std;

class Player {
public:
	Player();
	Player(string n, Team t);
	~Player();
	string getName();
	Team getTeam();
	int getPiecesRemaining();
	void decrementPiecesRemaining();
	
private:
	string name;
	Team team;
	int piecesRemaining;
};

#endif
