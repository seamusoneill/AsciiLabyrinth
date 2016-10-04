#include "Player.h"

Player::Player(){
	positionX = 5;
	positionY = 5;
	representation = 'P';
}
Player::~Player(){}

void Player::Move(){}
void Player::Move(Direction dir)
{
	switch (dir)
	{
	case UP:
		positionY += 1;
		break;
	case DOWN:
		positionY -= 1;
		break;
	case LEFT:
		positionX -= 1;
		break;
	case RIGHT:
		positionX += 1;
		break;
	default:
		break;
	}
}

char Player::GetRepresentation()
{
	return representation;
}

int Player::GetX()
{
	return positionX;
}

int Player::GetY()
{
	return positionY;
}