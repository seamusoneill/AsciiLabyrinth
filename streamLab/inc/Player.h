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
	void Look(Direction);
	bool GetHasShovel();
	void SetHasShovel(bool hS);
private:
	void PickUp();
	bool hasShovel;
	
};
#endif