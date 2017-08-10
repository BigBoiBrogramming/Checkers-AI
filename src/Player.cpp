#include "Player.h"

Player::Player(string n, Team t) : name(n), team(t), piecesRemaining(12)
{
}

Player::~Player()
{
}

string Player::getName()
{
	return name;
}

Team Player::getTeam()
{
	return team;
}

int Player::getPiecesRemaining()
{
	return piecesRemaining;
}

void Player::decrementPiecesRemaining()
{
	piecesRemaining--;
}
