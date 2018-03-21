#include "EntityManager.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager::EntityManager(const EntityManager& other)
{

}


EntityManager* EntityManager::GetInstance()
{
	if (!instance)
	{
		instance = new EntityManager();
	}

	return instance;
}

void EntityManager::RegisterEntity(int id, BaseGameEntity* newEntity)
{
	entityMap.insert(std::make_pair(newEntity->ID(), newEntity));
}

BaseGameEntity* EntityManager::GetEntityFromID(int id) const
{
	BaseGameEntity* searchedAgent = entityMap.at(id);
	return searchedAgent;
}

void EntityManager::RemoveEntity(BaseGameEntity* entity)
{
	std::map<int, BaseGameEntity*>::iterator it = entityMap.begin();
	it = entityMap.find(entity->ID());
	if (it != entityMap.end())
	{
		entityMap.erase(it);
	}
}

//Method to return all agents ID except for the one that calls the method
std::vector<int> EntityManager::GetAllEnttities(BaseGameEntity* entity)
{
	std::map<int, BaseGameEntity*>::iterator it = entityMap.begin();
	std::vector<int> arr;
	int index = 0;
	for(it ;it != entityMap.end(); it++)
	{
		if (it->first != entity->ID())
		{
			arr.push_back(it->first);
			index++;
		}
	}
	return arr;
}


