#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Entity.h"

class Monster : public Entity
{
public:
	Monster();
	void Initialise(point startPos);
	void Move(Direction dir);
};

#endif