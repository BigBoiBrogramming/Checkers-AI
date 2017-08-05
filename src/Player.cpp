#include "Player.h"

Player::Player(int number, string n) : playerNumber(number), name(n)
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
