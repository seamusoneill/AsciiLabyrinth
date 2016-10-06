#include "Player.h"

Player::Player(){

}
Player::~Player(){}

void Player::Initialise(point startPos)
{
	position = startPos;
	representation = 'O';
}

void Player::Move(Direction dir)
{
	switch (dir)
	{
	case UP:
		position.y -= 1;
		representation = '^';
		break;
	case DOWN:
		position.y += 1;
		representation = 'v';
		break;
	case LEFT:
		position.x -= 1;
		representation = '<';
		break;
	case RIGHT:
		position.x += 1;
		representation = '>';
		break;
	default:
		break;
	}
}