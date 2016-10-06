#include "CollisionManager.h"

CollisionManager* CollisionManager::m_instance = 0;
CollisionManager::CollisionManager(){}

CollisionManager* CollisionManager::instance(){
	if (m_instance == 0)
		m_instance = new CollisionManager();
	return m_instance;
}

bool CollisionManager::CheckCollision(Direction movingTo, Object* movingObject)
{
	switch (movingTo)
	{
	case UP:
		if (Level::GetLevelMap(movingObject->GetPosition().x,movingObject->GetPosition().y  -1)->GetType() == ObjectType::SOLID)
		{
			return false;
		}
	case DOWN:
		if (Level::GetLevelMap(movingObject->GetPosition().x, movingObject->GetPosition().y + 1)->GetType() == ObjectType::SOLID)
		{
			return false;
		}
		break;
	case LEFT:
		if (Level::GetLevelMap(movingObject->GetPosition().x - 1, movingObject->GetPosition().y)->GetType() == ObjectType::SOLID)
		{
			return false;
		}
		break;
	case RIGHT:
		if (Level::GetLevelMap(movingObject->GetPosition().x + 1, movingObject->GetPosition().y)->GetType() == ObjectType::SOLID)
		{
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}