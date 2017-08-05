#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player {
public:
	Player();
	Player(int number, string n);
	~Player();
	int getPlayerNumber();
	void setPlayerNumber(int& num);
	string getName();
	void setName(string& name);
	
private:
	int playerNumber;
	string name;
};

#endif
