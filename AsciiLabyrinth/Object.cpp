#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::OnTriggerEnter()
{
	switch (representation)
	{
		case 'ß':
			//Player.Death() ou Player->Death(); Monster
			break;
		case '/':
			//Player.PickUp() ou Player->PickUp(); Weapon
			break;
		case '¶':
			//Player.PickUp() ou Player->PickUp(); Key
			break;
		case '■':
			//Player.StopMove(); Wall
			break;
		case '­­║':
			//Player.StopMove(); Door
			break;
	}
}
