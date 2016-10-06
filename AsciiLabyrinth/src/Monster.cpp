#include "Monster.h"

Monster::Monster()
{
}

void Monster::Initialise(point startPos)
{
	position = startPos;
	representation = 'm';
}

void Monster::Move(Direction dir)
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