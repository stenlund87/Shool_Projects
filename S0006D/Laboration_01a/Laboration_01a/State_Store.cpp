#include <random>
#include <ctime>
#include <fstream>
#include "State.h"
#include "Agent.h"



bool State_Store::storeFlag = false;
State_Store* State_Store::storeInstance = nullptr;


State_Store::State_Store()
{

}

void State_Store::Enter(Agent* agent)
{
	if (agent->GetLocation() != Store)
	{
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Payday is the best day! Going shopping!" << std::endl;
		agent->ChangeLocation(Store);
	}
}

void State_Store::Exit(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": Leaving the store! My wallet is empty!" << std::endl;
	std::cout << "" << std::endl;
}

void State_Store::Execute(Agent* agent)
{

	//Sleep(timeToSleep);
	agent->SetInternalValues(Hungry, agent->Gains(Hungry));
	agent->SetInternalValues(Thirsty, agent->Gains(Thirsty));
	agent->SetInternalValues(Companionship, agent->Gains(Companionship));

	agent->SetTextColor(agent->GetColor());
	int shopping = rand() % 10;
	switch (shopping)
	{
	case 0:
		std::cout << agent->GetName() << ": Shovel!...for all the bodies!" << std::endl;
		agent->SetInternalValues(Cash, -10);
		break;
	case 1:
		std::cout << agent->GetName() << ": Food! Gotta fill that fridge" << std::endl;
		agent->SetInternalValues(Cash, -15);
		break;
	case 2:
		std::cout << agent->GetName() << ": Detergent! My clothes are dirty!" << std::endl;
		agent->SetInternalValues(Cash, -2);
		break;
	case 3:
		std::cout << agent->GetName() << ": BEER!!! There is a game on TV tonight!" << std::endl;
		agent->SetInternalValues(Cash, -10);
		break;
	case 4:
		std::cout << agent->GetName() << ": Gasoline! My car needs it" << std::endl;
		agent->SetInternalValues(Cash, -25);
		break;
	case 5:
		std::cout << agent->GetName() << ": Hunger games! This book seems good" << std::endl;
		agent->SetInternalValues(Cash, -15);
		break;
	case 6:
		std::cout << agent->GetName() << ": Call of Duty! Gotta buy that" << std::endl;
		agent->SetInternalValues(Cash, -18);
		break;
	case 7:
		std::cout << agent->GetName() << ": Knife! The old one is broken" << std::endl;
		agent->SetInternalValues(Cash, -10);;
		break;
	case 8:
		std::cout << agent->GetName() << ": Pencils! I never have a pencil when I need it" << std::endl;
		agent->SetInternalValues(Cash, -5);
		break;
	case 9:
		std::cout << agent->GetName() << ": Lottery! Time to get rich!" << std::endl;
		agent->SetInternalValues(Cash, -15);
		break;
	}
	if (agent->GetInternalValues(Cash) <= 15)
	{
		
		agent->CheckNextState(agent);
		//agent->GetFSM()->ChangeState(State_Home::GetInstance());
	}


}

State_Store* State_Store::GetInstance()
{
	if (!storeInstance)
	{
		storeInstance = new State_Store();
	}
	return storeInstance;

}

bool State_Store::OnMessage(Agent* agent, const Message& msg)
{
	switch (msg.msg)
	{
	case msg_Socialising:
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Receiving message: Socialising" << std::endl;
		if (agent->AcceptMessage())//<< Check if we can go and be social
		{
			Send->SendMessage(0.0f, msg.reciever, msg.sender, msg_Confirmed);
			Send->SendMessage(waitTime, agent->ID(), agent->ID(), msg_TimeToGo);
			agent->SetSocialMessage(true);
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