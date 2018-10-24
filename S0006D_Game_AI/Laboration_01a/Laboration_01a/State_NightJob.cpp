
#include <random>
#include <ctime>
#include <fstream>
#include "State.h"
#include "Agent.h"
#include "MessageSender.h"


bool State_Nightjob::nightFlag = false;
State_Nightjob* State_Nightjob::nightInstance = nullptr;


State_Nightjob::State_Nightjob()
{

}

void State_Nightjob::Enter(Agent* agent)
{
	if (agent->GetLocation() != Nightjob)
	{
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Nighttime! Time to get dangerous!" << std::endl;
		agent->ChangeLocation(Nightjob);
	}
}

void State_Nightjob::Execute(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": The streets are safe! Thanks to me" << std::endl;
	agent->SetInternalValues(Cash, agent->Gains(NightCash));
	agent->SetInternalValues(Tired, agent->Gains(Tired));
	agent->SetInternalValues(Hungry, agent->Gains(Hungry));
	agent->SetInternalValues(Thirsty, agent->Gains(Thirsty));

	if (agent->GetInternalValues(Cash) >= 100)
	{
		agent->CheckNextState(agent);
	}

}

void State_Nightjob::Exit(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": Leaving my superhero job! Time to go home! " << std::endl;
	std::cout << "" << std::endl;
}

State_Nightjob* State_Nightjob::GetInstance()
{
	if (!nightInstance)
	{
		nightInstance = new State_Nightjob();
	}
	return nightInstance;
}

bool State_Nightjob::OnMessage(Agent* agent, const Message& msg)
{
	switch (msg.msg)
	{
	case msg_Socialising:
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Receiving message: Socialising" << std::endl;
		Send->SendMessage(0.0f, msg.reciever, msg.sender, msg_Denied);
		std::cout << agent->GetName() << ": Sending message: Sorry, but I'm working the nightshift" << std::endl;
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