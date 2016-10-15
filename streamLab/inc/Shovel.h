#ifndef _SHOVEL_H_
#define _SHOVEL_H_
#pragma once

#include "Object.h"

class Shovel : public Object
{
public:
	Shovel();
	void Initialise(point startPos);
};
#endif