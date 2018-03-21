#pragma once
#ifndef BASEGAMEENTITY_H
#define BASEGAMEENTITY_H


#include "Message.h"
#include <assert.h>


class BaseGameEntity
{
	public:
		BaseGameEntity() { entityID = 0; name = "Bob"; };
		BaseGameEntity(int id){SetID(id);}
		BaseGameEntity(int id, char* agentName) 
		{
			SetName(agentName);
			SetID(id);
		};
		virtual ~BaseGameEntity() {}
		virtual void Update() = 0;
		virtual bool MessageHandler(const Message& msg) = 0;
		void SetName(char* agentName) { name = agentName; }
		char* GetName() { return name; };

		const int ID() { return entityID; }

	protected:
		void SetID(int val);

		int entityID; //<< Unique ID for entity
		static int nextID; //<< Next ID

		char* name;

};


#endif