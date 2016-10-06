#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::Initialise(point startPos)
{
	position = startPos;
}

void Object::OnTriggerEnter()
{}

char Object::GetRepresentation()
{
	return representation;
}

point Object::GetPosition(){
	return position;
}

ObjectType Object::GetType(){
	return type;
}