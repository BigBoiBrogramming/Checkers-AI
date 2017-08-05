#include "Player.h"

Player::Player(int number, string n, Team t) : playerNumber(number), name(n), team(t), piecesRemaining(12)
{
}

Player::~Player()
{
}

int Player::getPlayerNumber()
{
	return playerNumber;
}

void Player::setPlayerNumber(int& num)
{
	playerNumber = num;
}

string Player::getName()
{
	return name;
}

void Player::setName(string& name)
{
	this->name = name;
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
