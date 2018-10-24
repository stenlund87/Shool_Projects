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
	agent->SetInternalValues(Hungry, -15);
	agent->SetInternalValues(Cash, -10);
	agent->SetInternalValues(Tired, agent->Gains(Tired));
	agent->SetInternalValues(Companionship, agent->Gains(Companionship));

	if (agent->GetInternalValues(Hungry) <= 9)
	{
		agent->CheckNextState(agent);
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

bool State_Restaurant::OnMessage(Agent* agent, const Message& msg)
{
	switch (msg.msg)
	{
	case msg_Socialising:
		agent->SetTextColor(agent->GetColor()); 
		std::cout << agent->GetName() << ": Receiving message: Socialising" << std::endl;
		if (agent->AcceptMessage()) //<< Check if we can go and be social
		{
			agent->SetSocialMessage(true);
			Send->SendMessage(0.0f, msg.reciever, msg.sender, msg_Confirmed);
			Send->SendMessage(waitTime, agent->ID(), agent->ID(), msg_TimeToGo);
		}
		else
		{
			std::cout << agent->GetName() << ": Sending message: Sorry I'm too hungry to go out" << std::endl;
			Send->SendMessage(0.0f, msg.reciever, msg.sender, msg_Denied);
		}
		return true;
		break;
	case msg_Confirmed:
		if (!agent->GetReceivedMessage()) //<< Just to make it print just once if the first agent agrees
		{
			agent->SetTextColor(agent->GetColor());
			std::cout << agent->GetName() << ": Receiving message: Confirmed" << std::endl;
			Send->SendMessage(waitTime, agent->ID(), agent->ID(), msg_TimeToGo);
			agent->SetReceivedMessage(true); //<< Just to make sure we only do it once, in case we the agent also want to send a msg_Social
			agent->SetSocialMessage(true); //<< ....Same here
		}
		return true;
		break;
	case msg_Denied:
		agent->deniedRecieved++;
		if (agent->deniedRecieved == 3)
		{
			agent->SetInternalValues(Companionship, -agent->GetInternalValues(Companionship)); //<< We dont want the agent to spam the rest with messages
			agent->SetSocialMessage(false);

			agent->SetTextColor(agent->GetColor());
			std::cout << agent->GetName() << ": FINE BY ME! I'LL JUST MAKE NEW FRIENDS!!!" << std::endl;
			agent->deniedRecieved = 0;
		}
		return true;
		break;

	case msg_TimeToGo:
		agent->deniedRecieved = 0;
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Receiving message: Time to go" << std::endl;
		agent->GetFSM()->ChangeState(State_Social::GetInstance());
		agent->SetReceivedMessage(false); //<< So we can send a social message in the future
		agent->SetSocialMessage(false);
		return true;
		break;
	}

	return false;
}
