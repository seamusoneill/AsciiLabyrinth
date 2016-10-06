#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

#include "Entity.h"

class Player : public Entity{
public:
	Player();
	~Player();
	
	void Initialise(point startPos);
	void Move(Direction);
private:
	void PickUp();
	
};
#endif