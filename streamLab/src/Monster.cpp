#include "Monster.h"


Monster::Monster()
{
}


Monster::~Monster()
{
}

void Monster::Initialise(point startPos)
{
	position.x = startPos.x;
	position.y = startPos.y;
	representation = '§';
}

void Monster::Move(Direction dir)
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

void Monster::Test(int x, int y)
{
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{

		}
	}
}

void Monster::Update()
{

}

