
#include <random>
#include <ctime>
#include <fstream>
#include "State.h"
#include "Agent.h"


bool State_Home::homeFlag = false;
State_Home* State_Home::homeInstance = nullptr;


void State_Home::Enter(Agent* agent)
{
	if (agent->GetLocation() != Home)
	{
		std::cout << agent->GetName() << ": Going home, I'm so tired!" << std::endl;
		agent->ChangeLocation(Home);
	}
}

void State_Home::Execute(Agent* agent)
{
		std::cout << agent->GetName() << ": ZZZzzzzzZZZZzzzzz" << std::endl;
		agent->SetInternalValues(Tired, -25);
		agent->SetInternalValues(Hungry, agent->Gains(Hungry));
		agent->SetInternalValues(Thirsty, agent->Gains(Thirsty));

		if (agent->GetInternalValues(Tired) <= 15)
		{
			agent->CheckNextState(agent);
		}
}

void State_Home::Exit(Agent* agent)
{
	std::cout << agent->GetName() << ": Rise and shine! Nothing beats a good night rest" << std::endl;
	std::cout << "" << std::endl;
}

 State_Home* State_Home::GetInstance()
{
	 if (!homeInstance)
	 {
		 homeInstance = new State_Home();
	 }
	 return homeInstance;
}

 bool State_Home::OnMessage(Agent* agent, const Message& msg)
 {
	 switch (msg.msg)
	 {
		 //Because we are sleeping we send a msg_Denied to sender
	 case msg_Socialising: 
		 agent->SetTextColor(agent->GetColor());
		 std::cout << agent->GetName() << ": Receiving message: Socialising" << std::endl;
		 Send->SendMessage(0.0f, msg.reciever, msg.sender, msg_Denied);
		 std::cout << agent->GetName() << ": Sending message: ZzzzzZZzzzZZZzzz....I'm sleeping!" << std::endl;
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