#include "Wall.h"

Wall::Wall()
{
	
}
void Wall::Initialise(point startPos)
{
	representation = '|';
	position = startPos;
	type = ObjectType::Solid;
}

Wall::~Wall()
{}

