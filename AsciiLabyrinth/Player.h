#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

#include "Entity.h"

enum Direction
{ 
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player : public Entity{
public:
	Player();
	~Player();
	
	void Move();
	void Move(Direction);

	char GetRepresentation();
	int GetX();
	int GetY();
private:
	void PickUp();
	
};
#endif