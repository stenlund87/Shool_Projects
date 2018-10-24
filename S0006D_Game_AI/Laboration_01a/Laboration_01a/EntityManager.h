#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#define EntityMgr EntityManager::GetInstance()
#include <map>
#include <cassert>
#include <vector>
#include "BaseGameEntity.h"


class EntityManager
{

	public:
		static EntityManager* GetInstance();		//<<Returns the singleton pointer

		void RegisterEntity(int id, BaseGameEntity* newEntity);  //<< Insert the entity to map with ID as key
		BaseGameEntity* GetEntityFromID(int id) const; //<< Finds the entity from ID and returns it's pointer
		void RemoveEntity(BaseGameEntity* entity);     //<< Removes the entity from the map
		std::vector<int> GetAllEnttities(BaseGameEntity* entity);  //<< Returns a vector containing all other Agents ID

	private:
		EntityManager() {};

		EntityManager(const EntityManager& other);
		EntityManager& operator=(const EntityManager& other);

		std::map<int, BaseGameEntity*> entityMap;

		static EntityManager* instance;


};

#endif