#pragma once
#ifndef STATE_H
#define STATE_H
//#include "MessageDispatcher.h"

#include "Message.h"
#include "EntityManager.h"
#include <vector>

const double waitTime = 20.0;

class Agent;
struct Message;

template<class entity_type>
class State
{
	public:
		virtual ~State() {};

		virtual void Enter(entity_type* agent) = 0; //<< Enter the state for all subclasses
		virtual void Execute(entity_type* agent) = 0; //<< Executes the code for all subclasses
		virtual void Exit(entity_type* agent) = 0; //<< Exit the state and enters the next
		virtual bool OnMessage(entity_type* agent, const Message& msg) = 0; //<< Handle the message for all subclasses
		
		const int timeToSleep = 500;

	private:

};

class Global_State : public State<Agent>
{
public:
	~Global_State(){};
	void Enter(Agent* agent);
	void Execute(Agent* agent);
	void Exit(Agent* agent);
	static Global_State* GetInstance();
	bool OnMessage(Agent* agent, const Message& msg);


private:
	Global_State();

	Global_State(const Global_State&);

};


class State_Work : public State<Agent>
{
	public:
		~State_Work()
		{
			workInstance = nullptr;
			workFlag = false;
		};
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Work* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);


	private:
		State_Work();
		static State_Work* workInstance;
		static bool workFlag;
};

class State_Nightjob : public State<Agent>
{
	public:
		~State_Nightjob()
		{
			nightInstance = nullptr;
			nightFlag = false;
		}
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Nightjob* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);


	private:
		State_Nightjob();
		static State_Nightjob* nightInstance;
		static bool nightFlag;
};

class State_Home: public State<Agent>
{
	public:
		~State_Home()
		{
			homeInstance = nullptr;
			homeFlag = false;
		};
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Home* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);


	private:
		State_Home() {};
		static State_Home* homeInstance;
		static bool homeFlag;
};

class State_Store : public State<Agent>
{
	public:
		~State_Store() 
		{
			storeInstance = nullptr;
			storeFlag = false;
		}
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Store* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);


	private:
		State_Store();
		enum ShoppingList
		{
			Shovel,
			Food,
			Detergent,
			Beer,
			Gasoline,
			Books,
			Games,
			Knife,
			Pencil,
			Lottery
		};

		static State_Store* storeInstance;
		static bool storeFlag;
};

class State_Social : public State<Agent>
{
	public:
		~State_Social()
		{ 
			socialInstance = nullptr; 
			socialFlag = false;
		};
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Social* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);


	private:
		State_Social();
		static State_Social* socialInstance;
		static bool socialFlag;

};

class State_Pub : public State<Agent>
{
	public:

		~State_Pub() 
		{
			pubInstance = nullptr;
			pubFlag = false;
		};
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Pub* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);


	private:
		State_Pub() {};
		static State_Pub* pubInstance;
		static bool pubFlag;
};

class State_Restaurant : public State<Agent>
{
	public:
		~State_Restaurant() 
		{
			restaurantInstance = nullptr;
			resturantFlag = false;
		};
		void Enter(Agent* agent);
		void Execute(Agent* agent);
		void Exit(Agent* agent);
		static State_Restaurant* GetInstance();
		bool OnMessage(Agent* agent, const Message& msg);

		private:
			State_Restaurant() {};
			static State_Restaurant* restaurantInstance;
			static bool resturantFlag;

};
#endif