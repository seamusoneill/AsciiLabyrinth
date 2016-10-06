#ifndef _WALL_H_
#define _WALL_H_
#pragma once

#include "Object.h"

class Wall : public Object {
public: 
	Wall();
	~Wall();
	void Initialise(point startPos);
};

#endif