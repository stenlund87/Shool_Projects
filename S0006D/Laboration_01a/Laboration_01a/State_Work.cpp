
#include <random>
#include <ctime>
#include <fstream>
#include "State.h"
#include "Agent.h"

#define Send MessageSender::GetInstance()

bool State_Work::workFlag = false;
State_Work* State_Work::workInstance = nullptr;

State_Work::State_Work()
{

}

void State_Work::Enter(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	if (agent->GetLocation() != Work)
	{

		std::cout << agent->GetName() << ": Time to go to work!" << std::endl;
		agent->ChangeLocation(Work);
	}
}

void State_Work::Execute(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": Getting money in my pocket" << std::endl;
	agent->SetInternalValues(Cash, agent->Gains(Cash));
	agent->SetInternalValues(Tired, agent->Gains(Tired));
	agent->SetInternalValues(Hungry, agent->Gains(Hungry));
	agent->SetInternalValues(Thirsty, agent->Gains(Thirsty));
	agent->SetInternalValues(Companionship, agent->Gains(Companionship));

	if (agent->GetInternalValues(Cash) > 65)
	{
		agent->CheckNextState(agent);
	}
}

void State_Work::Exit(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": Leaving work! I have made so much money" << std::endl;
	std::cout << "" << std::endl;
}

State_Work* State_Work::GetInstance()
{
	if (!workInstance)
	{
		workInstance = new State_Work();
	}
	return workInstance;
}

bool State_Work::OnMessage(Agent* agent, const Message& msg)
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
			std::cout << agent->GetName() << ": Sending message: Sure! Let's meet up in two hours! I need to finish work!" << std::endl;
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
