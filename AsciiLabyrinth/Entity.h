#pragma once
#include "Object.h"

class Entity :
	public Object
{
	public:
		Entity();
		~Entity();

		virtual void Move() = 0;
		void Death();
		void Attack();

	protected:
		int life;
};

