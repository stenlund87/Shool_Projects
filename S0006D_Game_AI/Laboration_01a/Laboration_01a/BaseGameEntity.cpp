#include "BaseGameEntity.h"
#include <iostream>

int BaseGameEntity::nextID = 0;

void BaseGameEntity::SetID(int val)
{
	//Checks if the entity can have that ID, we don't want two entities with the same ID
	if (val >= nextID)
	{
		entityID = val;
		nextID = entityID + 1;
	}
	else
	{
		entityID = nextID;
		nextID++;
		std::cout << "Invalid ID for agent "<< GetName()<< "! Agent ID is set to: " << entityID << std::endl;
	}
}