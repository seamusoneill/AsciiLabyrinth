#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_
#pragma once
//Singleton CollisionManager. Check here if two objects collide.

#include "Entity.h"
#include "Level.h"

class CollisionManager{
public :
	static CollisionManager* instance();

	bool CheckCollision(Direction direction, Object* movingObject);

private:
	static CollisionManager* m_instance;
	CollisionManager();

};

#endif