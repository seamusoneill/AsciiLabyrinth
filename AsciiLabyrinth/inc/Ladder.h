#ifndef _LADDER_H_
#define _LADDER_H_

#include "Object.h"

class Ladder : public Object{
public:
	Ladder();
	void Initialise(point startPos);
};

#endif