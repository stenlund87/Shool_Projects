#pragma once
#ifndef AGENT_H
#define AGENT_H


#include <iostream>
#include <string.h>
#include "State.h"
#include "BaseGameEntity.h"
#include "FiniteStateMachine.h"
#include "MessageSender.h"


//Integers used for threshold point in each state
const int tiredThreshold = 100;
const int hungertThreshold = 100;
const int thirstThreshold = 85;
const int cashThresholdTop = 100;
const int cashThresholdLow = 10;
const int socialThreshold = 80;
const int salaryThreshold = 73;



struct Message;

enum Location
{
	Work,
	Nightjob,
	Home,
	Store,
	Social,
	Travel,
	Restaurant,
	Pub
};


enum InternalValues
{
	Hungry,
	Thirsty,
	Tired,
	Cash,
	Companionship,
	NightCash

};




class Agent: public BaseGameEntity
{
	public:
		//Constructors for agent ID, name
		Agent(int id, char* agentName);

		//Constructor for agent ID, name, salary for the different jobs.
		Agent(int id, char* agentName, int workSal, int nightSal);

		~Agent();

		//General methods to change states etc
		void Update();
		FiniteStateMachine<Agent>* GetFSM() const { return stateMachine; };
		void ChangeState(State<Agent>* newState); //<< Changes the agents state

		//Setter methods
		void RandomState(); //<< Sets random State for the agent
		void RandomInternal(); //<< Sets random internal values for hunger, thirst etc
		void ChangeLocation(Location loc); //<< Changes the location for the agent

		/**
		*@param InternvalValues intVal, enum for which value that will be changed
		*@param int val, value for the internal value
		*/
		void SetInternalValues(InternalValues intVal, int val);
		void SetGains(int hngr, int thrst, int fati, int soc); //<< Sets the increase for the internal values for each Update()
		void SetSocialMessage(bool val) { sentSocialMessage = val; }; 
		void SetReceivedMessage(bool val) { recievedConfirmedMessage = val; };
		void SetColor(int col) { colorCode = col; };
		inline void SetTextColor(int colors) //<< Sets the color that the console prints out
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, colors);
		};

		//Getter methods
		Location GetLocation();
		int GetInternalValues(InternalValues intVal); //<< Returns the internal value that the agent asks for
		int Gains(InternalValues inVal); //<< Returns the gains for the agent
		int GetColor() { return colorCode; }
		bool GetSocialMessage() { return sentSocialMessage; };
		bool GetReceivedMessage() { return recievedConfirmedMessage; };



		//Methods to check which State the agent should go to next
		void CheckNextState(Agent* agent);

		//Methods for checking/accepting message
		bool MessageHandler(const Message& msg);
		bool AcceptMessage(); //<< Checks if the agent can go to State_Social

		int deniedRecieved = 0;

	private:

		//Hidden variables that dictates which state the agent should be in
		int hunger = 0;
		int thirst = 0;
		int fatigue = 0;
		int money = 0;
		int socialNeeds = 0;

		//Base values that represents the agents salary, hunger gain etc
		int workSalary = 15;
		int nightSalary = 10;
		int hungerGain = 2;
		int thirstGain = 4;
		int fatigueGain = 3;
		int socialGain = 8;


		//bool that is used by the agent that is sending msg_Social to the rest
		bool sentSocialMessage = false;
		bool recievedConfirmedMessage = false;

		//Different pointers
		FiniteStateMachine<Agent>* stateMachine;
		State<Agent>* currentState = nullptr;
		Location currentLocation;
		int colorCode;
};

#endif