#pragma once
#include <math.h>

//Enum that contains different types of messages
enum MessageTypes
{
	msg_Socialising,
	msg_Confirmed,
	msg_Denied,
	msg_TimeToGo,
	msg_Leaving
};


struct Message
{
	int sender;
	int reciever;
	int msg;

	double timeToSend;

	Message()
	{
		timeToSend = -1;
		sender = -1;
		reciever = -1;
		msg = -1;
	};

	Message(double time, int p_sender, int p_receiver, int msg_type)
	{
		sender = p_sender;
		reciever = p_receiver;
		msg = msg_type;
	};

	//Simple method to enable us to print what type of message 
	char* MessageToString() const
	{
		switch (this->msg)
		{
		case msg_Socialising:
			return "Socialising";
			break;
		case msg_Confirmed:
			return "Confirmed";
			break;
		case msg_Denied:
			return "Denied";
			break;
		case msg_TimeToGo:
			return "Time to go";
			break;
		case msg_Leaving:
			return "Leaving";
			break;
		default:
			break;
		}

	};
};

inline bool operator==(const Message& msg1, const Message& msg2)
{
	return (fabs(msg1.timeToSend - msg2.timeToSend) < 0.25f) && (msg1.sender == msg2.sender) && (msg1.reciever == msg2.reciever) && (msg1.msg == msg2.msg);
};

inline bool operator< (const Message& msg1, const Message& msg2)
{
	if (msg1 == msg2)
	{
		return false;
	}
	else
	{
		return (msg1.timeToSend < msg2.timeToSend);
	}
};