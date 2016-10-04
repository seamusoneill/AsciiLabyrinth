#ifndef _OBJECT_H_
#define _OBJECT_H_
#pragma once

using namespace std;

class Object
{
	enum ObjectType
	{
		Trigger,
		Solid
	};

	public:
		Object();
		~Object();

		void OnTriggerEnter();

	protected:
		int positionX, positionY;
		char representation;

	private:
		ObjectType type;
};

#endif