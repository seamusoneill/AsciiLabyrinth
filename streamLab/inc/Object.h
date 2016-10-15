#ifndef _OBJECT_H_
#define _OBJECT_H_
#pragma once

using namespace std;

struct point{ 
	int x; 
	int y;
	point(){};
	point(int xVal, int yVal) : x(xVal), y(yVal){};
};

enum ObjectType
{
	Trigger,
	Solid
};

class Object
{
	public:
		Object();
		~Object();
		void Initialise(point startPos);
		virtual void OnTriggerEnter();
		char GetRepresentation();
		point GetPosition();
		ObjectType GetType();
	protected:
		point position;
		char representation;
		ObjectType type;
};

#endif