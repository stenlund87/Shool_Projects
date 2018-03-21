#pragma once
#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H
#include <chrono>
#include <thread>
#include <vector>
#include <assert.h>
#include "Message.h"
#include "State.h"

template <class entity_type>
class FiniteStateMachine
{
	public:
		FiniteStateMachine(entity_type* p_owner)
		{
			owner = p_owner;
			currentState = nullptr;
			prevState = nullptr;
		}

		void SetCurrentState(State<entity_type>* s) { currentState = s; };
		void SetPreviousState(State<entity_type>* s) { prevState = s; };

		void Update() const
		{
			if (currentState)
			{
				currentState->Execute(owner);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		}

		void ChangeState(State<entity_type>* newState)
		{
			assert(newState && "<StateMachine::ChangeState>: trying to change to a null state");

			prevState = currentState;
			prevState->Exit(owner);
			currentState = newState;
			currentState->Enter(owner);
		};

		void RevertToPreviousState()
		{
			ChangeState(prevState);
		};

		State<entity_type>* CurrrentState() { return currentState; };
		State<entity_type>* PreviousState() { return prevState; };

		//Returns true if the current state's type is equal to the type of the class passed as a parameter
		bool IsInState(const State<entity_type>& st)const
		{ 
			if (typeid(*currentState) == typeid(st))
			{
				return true;
			}
			return false;
		};

		bool HandleMessage(const Message& msg) const
		{
			if (currentState && currentState->OnMessage(owner, msg))
			{
				return true;
			}
		};

	private:
		entity_type* owner;

		State<entity_type>* currentState;
		State<entity_type>* prevState;
};
#endif