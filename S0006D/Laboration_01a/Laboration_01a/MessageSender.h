#pragma once
#pragma once

#ifndef MESSAGE_SENDER_H
#define MESSAGE_SENDER_H


#include <set>
#include "Message.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "ConsoleUtils.h"

class BaseGameEntity;

class MessageSender
{
public:

	static MessageSender* GetInstance(); //<< Returns the pointer to the singleton
	void SendMessage(double delay, int sender, int receiver, int msg); //<< Sends the message if delay == 0, otherwise put it in queue
	void SendDelayedMessages(); //<< Sends the message in queue if delay == 0

private:
	MessageSender() {};

	void SendNow(BaseGameEntity* reciever, const Message& msg); //<< Send the message to receiver
	std::set<Message> priorityQueue;
	static MessageSender* instance;

};
//Just to make my life simple
#define Send MessageSender::GetInstance() 

#endif