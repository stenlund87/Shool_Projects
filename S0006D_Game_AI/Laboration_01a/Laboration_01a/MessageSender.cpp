#include <ctime>
#include <iostream>
#include <chrono>
#include "MessageSender.h"


#define Send MessageSender::GetInstance()


MessageSender* MessageSender::instance = nullptr;

MessageSender* MessageSender::GetInstance()
{
	if (!instance)
	{
		instance = new MessageSender();
	}
	return instance;
}

void MessageSender::SendMessage(double delay, int sender, int receiver, int msg)
{
	BaseGameEntity* agentSender = EntityMgr->GetEntityFromID(sender);
	BaseGameEntity* agentReciever = EntityMgr->GetEntityFromID(receiver);

	if (agentReciever == nullptr)
	{
		std::cout << "Warning! No receiver found with ID " << receiver << std::endl;
	}

	Message telegram(0, sender, receiver, msg);
	if (delay <= 0.0f)
	{
		std::cout << "Message sent to " << agentReciever->GetName() << " of type: " << telegram.MessageToString()<< " From: "<< agentSender->GetName() << std::endl;
		SendNow(agentReciever, telegram);
	}
	else
	{
		std::chrono::time_point<std::chrono::system_clock>start, end;
		start = std::chrono::system_clock::now();
		std::chrono::duration<double> currentTime = start-end;
		telegram.timeToSend = delay + currentTime.count();
		priorityQueue.insert(telegram);
	}

}

void MessageSender::SendDelayedMessages()
{
	std::chrono::time_point<std::chrono::system_clock>start, end;
	start = std::chrono::system_clock::now();
	std::chrono::duration<double> time = start - end;
	double currentTime = time.count();
	while (!priorityQueue.empty() && (priorityQueue.begin()->timeToSend < currentTime) && (priorityQueue.begin()->timeToSend > 0))
	{
		//Get the telegram from the front of the queue
		const Message& telegram = *priorityQueue.begin();

		//Find the reciever
		BaseGameEntity* agentReceiver = EntityMgr->GetEntityFromID(telegram.reciever);

		std::cout << "Message sent to " << agentReceiver->GetName() << " of type: " << telegram.MessageToString() <<std::endl;
		SendNow(agentReceiver, telegram);

		//Delete the msg
		priorityQueue.erase(priorityQueue.begin());
	}
}

void MessageSender::SendNow(BaseGameEntity* reciever, const Message& msg)
{
	if (!reciever->MessageHandler(msg)) //<< If MessageHandler returns false
	{
		std::cout << "Message not handled" << std::endl;
		std::cout << "" << std::endl;
	}
}

