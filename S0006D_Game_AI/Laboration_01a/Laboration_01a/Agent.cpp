#include<random>
#include <ctime>
#include "Agent.h"
//#include "MessageDispatcher.h"


Agent::Agent(int id, char* agentName):BaseGameEntity(id, agentName)
{
	this->name = agentName;
	RandomInternal(); //<< Sets random internal values for the agent
	currentLocation = Home;

	stateMachine = new FiniteStateMachine<Agent>(this);
	stateMachine->SetCurrentState(State_Home::GetInstance());
	EntityMgr->RegisterEntity(entityID, this); 
}

Agent::Agent(int id, char* agentName , int workSal, int nightSal) :BaseGameEntity(id, agentName)
{
	workSalary = workSal;
	nightSalary = nightSal;
	RandomInternal(); //<< Registers the entity
	currentLocation = Home;

	stateMachine = new FiniteStateMachine<Agent>(this);
	stateMachine->SetCurrentState(State_Home::GetInstance());
	EntityMgr->RegisterEntity(entityID, this);	//<< Registers the entity
}

Agent::~Agent()
{
	EntityMgr->RemoveEntity(this);
	delete stateMachine;
	delete name;

}

void Agent::Update()
{
	SetTextColor(this->colorCode);
	thirst++;
	hunger++;
	socialNeeds++;
	stateMachine->Update();
}


void Agent::ChangeState(State<Agent>* newState)
{
	assert(currentState && newState);
	currentState->Exit(this);
	currentState = newState;
	currentState->Enter(this);
}

Location Agent::GetLocation()
{
	return currentLocation;
}

void Agent::ChangeLocation(Location loc)
{
	currentLocation = loc;
}

void Agent::SetInternalValues(InternalValues intVal, int val)
{
	switch (intVal)
	{
	case Cash:
		money += val;
		break;
	case Tired:
		fatigue += val;
		break;
	case Companionship:
		socialNeeds += val;
		break;
	case Hungry:
		hunger += val;
		break;
	case Thirsty:
		thirst += val;
		break;
	default:
		break;
	}

	//Just to make sure that no value goes below 0, may never go above else
	if (money < 0) 
	{
		money = 0;
	}
	if (thirst < 0)
	{
		thirst = 0;
	}
	if (socialNeeds < 0)
	{
		socialNeeds = 0;
	}
	if (hunger < 0)
	{
		hunger = 0;
	}
	if (fatigue < 0)
	{
		fatigue = 0;
	}
}

int Agent::GetInternalValues(InternalValues intVal)
{
	switch (intVal)
	{
	case Hungry:
		return hunger;
		break;
	case Thirsty:
		return thirst;
		break;
	case Tired:
		return fatigue;
		break;
	case Cash:
		return money;
		break;
	case Companionship:
		return socialNeeds;
		break;
	}
	return 0;
}

//Method to set up some difference for the agent, optional
void Agent::SetGains(int hngr, int thrst, int fati, int soc)
{
	hungerGain = hngr;
	thirst = thrst;
	fatigue = fati;
	socialGain = soc;
}

int Agent::Gains(InternalValues inVal)
{
	switch (inVal)
	{
	case Hungry:
		return hungerGain;
		break;
	case Thirsty:
		return thirstGain;
		break;
	case Tired:
		return fatigueGain;
		break;
	case Cash:
		return workSalary;
		break;
	case Companionship:
		return socialGain;
		break;
	case NightCash:
		return nightSalary;
		break;
	}
	return 0;
}

//Method to check what the next state is depending of the internal values
void Agent::CheckNextState(Agent* agent)
{
	if (GetInternalValues(Tired) >= tiredThreshold)
	{
		agent->GetFSM()->ChangeState(State_Home::GetInstance());
	}
	else if (agent->GetInternalValues(Hungry) >= hungertThreshold)
	{
		agent->GetFSM()->ChangeState(State_Restaurant::GetInstance());
	}
	else if (agent->GetInternalValues(Thirsty) >= thirstThreshold)
	{
		agent->GetFSM()->ChangeState(State_Pub::GetInstance());
	}
	else if (agent->GetInternalValues(Cash) >= cashThresholdTop)
	{
		agent->GetFSM()->ChangeState(State_Store::GetInstance());
	}
	else if (agent->GetInternalValues(Companionship) >= socialThreshold && !agent->GetSocialMessage())
	{
		std::vector<int> arr = EntityMgr->GetAllEnttities(agent);
		for (int i = 0; i < arr.size(); i++)
		{
			Send->SendMessage(0.0f, this->ID(), arr.at(i), msg_Socialising);
		}

	}
	else if(agent->GetInternalValues(Cash) >= salaryThreshold)
	{
		agent->GetFSM()->ChangeState(State_Nightjob::GetInstance());
	}
	else if(agent->GetInternalValues(Cash) < cashThresholdLow)
	{
		agent->GetFSM()->ChangeState(State_Work::GetInstance());
	}

}

//Sets the currentState as random, optional
void Agent::RandomState()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int>random(0, 600);
	int bla = random(rng);
	bla = bla/100;
	
	switch (bla)
	{
	case 0:
		this->fatigue = 45;
		this->currentState = State_Home::GetInstance();
		break;
	case 1:
		this->money = 67;
		this->currentState = State_Nightjob::GetInstance();
		break;
	case 2:
		this->thirst = 73;
		this->currentState = State_Pub::GetInstance();
		break;
	case 3:
		this->hunger = 55;
		this->currentState = State_Restaurant::GetInstance();
		break;
	case 4:
		this->socialNeeds = 0;
		this->currentState = State_Social::GetInstance();
		break;
	case 5:
		this->money = 78;
		this->currentState = State_Store::GetInstance();
		break;
	case 6:
		this->currentState = State_Work::GetInstance();
		break;
	}
}

//Random internal values, so the agents can differentiate from eachother
void Agent::RandomInternal()
{
	int i = 0;
	while (i < 5)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int>random(0, 1000);
		int val = random(rng);
		val = val * 0.1;

		switch (i)
		{
		case 0:
			this->hunger = val;
			break;
		case 1:
			this->thirst = val;
			break;
		case 2:
			this->fatigue = val;
			break;
		case 3:

			this->money = val;
			break;
		case 4:
			this->socialNeeds = val;
			break;
		default:
			break;
		}
		i++;
	}

}

bool Agent::MessageHandler(const Message& msg)
{
	return stateMachine->HandleMessage(msg);
}

bool Agent::AcceptMessage()
{
	return (this->hunger <= 75);
}