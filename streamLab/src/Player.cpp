#include "Player.h"

Player::Player(){

}
Player::~Player(){}

void Player::Initialise(point startPos)
{
	position = startPos;
	representation = 'O';
	hasShovel = false;
}

void Player::Move(Direction dir)
{
	switch (dir)
	{
	case UP:
		position.y -= 1;
		break;
	case DOWN:
		position.y += 1;
		break;
	case LEFT:
		position.x -= 1;
		break;
	case RIGHT:
		position.x += 1;
		break;
	default:
		break;
	}
}

void Player::Look(Direction looking)
{
	switch (looking)
	{
	case UP:
		representation = '^';
		break;
	case DOWN:
		representation = 'v';
		break;
	case LEFT:
		representation = '<';
		break;
	case RIGHT:
		representation = '>';
		break;
	default:
		break;
	}
}

bool Player::GetHasShovel()
{
	return hasShovel;
}
void Player::SetHasShovel(bool hS)
{
	hasShovel = hS;
}