#pragma once
#include "Entity.h"
class Monster :
	public Entity
{
public:
	Monster();
	~Monster();

	void Initialise(point startPos);
	void Move(Direction);
	void Test(int x, int y);
	void Update();
};

