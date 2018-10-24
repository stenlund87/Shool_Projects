#pragma once
#include <random>
#include <ctime>
#include <fstream>
#include "State.h"
#include "Agent.h"


bool State_Restaurant::resturantFlag = false;
State_Restaurant* State_Restaurant::restaurantInstance = nullptr;

void State_Restaurant::Enter(Agent* agent)
{
	if (agent->GetLocation() != Restaurant)
	{
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": I'm getting hungry! Time to get some grub" << std::endl;
		agent->ChangeLocation(Restaurant);
	}
}

void State_Restaurant::Execute(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": This food is really good!" << std::endl;
	agent->SetInternalValues(Hungry, -25);
	agent->SetInternalValues(Cash, -10);
	agent->SetInternalValues(Tired, agent->Gains(Tired));
	agent->SetInternalValues(Companionship, agent->Gains(Companionship));

	if (agent->GetInternalValues(Hungry) <= 9)
	{
		agent->GetFSM()->RevertToPreviousState();
		//agent->CheckNextState(agent);
	}
}

void State_Restaurant::Exit(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": Leaving the restaurant! My stomach is so full!" << std::endl;
	std::cout << "" << std::endl;
}

State_Restaurant* State_Restaurant::GetInstance()
{
	if (!restaurantInstance)
	{
		restaurantInstance = new State_Restaurant();
	}
	return restaurantInstance;
}

bool State_Restaurant::OnMessage(Agent* agent, const Telegram& msg)
{
	switch (msg.msg)
	{
	case msg_Socialising:
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Receiving message: Socialising" << std::endl;
		if (agent->AcceptMessage())
		{
			Send->DispatchMessage(0.0f, msg.reciever, msg.sender, msg_Confirmed);
			Send->DispatchMessage(2.0f, agent->ID(), agent->ID(), msg_TimeToGo);
			return true;
		}
		std::cout << agent->GetName() << ": Sending message: Sorry I'm too hungry to go out" << std::endl;
		return false;
		break;
	case msg_Confirmed:
		if (!agent->GetReceivedMessage())
		{
			agent->SetTextColor(agent->GetColor());
			std::cout << agent->GetName() << ": Receiving message: Confirmed" << std::endl;
			Send->DispatchMessage(2.0f, agent->ID(), agent->ID(), msg_TimeToGo);
			agent->SetReceivedMessage(true);
		}

		return true;
		break;
	case msg_TimeToGo:
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Receiving message: Time to go" << std::endl;
		agent->GetFSM()->ChangeState(State_Social::GetInstance());
		agent->SetReceivedMessage(false);
		return true;
		break;
	}

	return false;
}

void State_Restaurant::AddMember(Agent* agent)
{
	entityVector.push_back(agent);
}

void State_Restaurant::CheckMembers()
{
	if (entityVector.size() > 1)
	{
		for (int i = 0; i < entityVector.size(); i++)
		{
			entityVector[i]->SetInternalValues(Companionship, 9);
		}

	}
}

void State_Restaurant::RemoveMember(Agent* agent)
{
	if (entityVector.size() > 0)
	{
		for (int i = 0; i < entityVector.size(); i++)
		{
			if (entityVector[i] == agent)
			{
				entityVector.erase(entityVector.begin() + i);
			}
		}
	}
}