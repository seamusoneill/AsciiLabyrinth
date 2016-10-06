#include "Ladder.h"

Ladder::Ladder()
{}

void Ladder::Initialise(point startPos)
{
	position = startPos;
	representation = '!';
	type = Trigger;
}
