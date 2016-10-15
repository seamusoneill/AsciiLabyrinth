#pragma once
#include "Object.h"

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Entity :
	public Object
{
	public:
		Entity();
		~Entity();

		virtual void Move(Direction movingTo) = 0;
		void Death();
		void Attack();

	protected:
		int life;
};

