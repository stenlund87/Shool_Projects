#include <random>
#include <ctime>
#include <fstream>
#include "State.h"
#include "Agent.h"



bool State_Social::socialFlag = false;
State_Social* State_Social::socialInstance = nullptr;


State_Social::State_Social()
{

}

void State_Social::Enter(Agent* agent)
{
	if (agent->GetLocation() != Social)
	{
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Going out to meet my friends" << std::endl;
		agent->ChangeLocation(Social);
	}
}

void State_Social::Execute(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": Having fun with my friends" << std::endl;
	std::cout << "" << std::endl;
	agent->SetInternalValues(Companionship, -25);
	agent->SetInternalValues(Hungry, agent->Gains(Hungry));

	if (agent->GetInternalValues(Companionship) <= 15)
	{	
		std::vector<int> arr = EntityMgr->GetAllEnttities(agent);
		for (int i = 0; i < arr.size(); i++)
		{
			Send->SendMessage(0.0f,agent->ID(),arr.at(i), msg_Leaving);
		}
		agent->GetFSM()->ChangeState(State_Home::GetInstance());
	}
}

void State_Social::Exit(Agent* agent)
{
	agent->SetTextColor(agent->GetColor());
	std::cout << agent->GetName() << ": I'm leaving the bowling hall" << std::endl;
	std::cout << "" << std::endl;
}

State_Social* State_Social::GetInstance()
{
	if (!socialInstance)
	{
		socialInstance = new State_Social();
	}
	return socialInstance;
}

bool State_Social::OnMessage(Agent* agent, const Message& msg)
{
	switch (msg.msg)
	{
	case msg_Leaving:
		agent->SetInternalValues(Tired, 80);
		agent->SetTextColor(agent->GetColor());
		std::cout << agent->GetName() << ": Recieving message: Leaving" << std::endl;
		agent->GetFSM()->ChangeState(State_Home::GetInstance());
		return true;
		break;
	}

	return false;
}