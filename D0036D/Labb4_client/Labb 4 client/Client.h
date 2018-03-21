#pragma once
#pragma comment(lib, "ws2_32.lib")
#define MAXNAMELEN 32
#define DEFAULT_BUFLEN 512
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>

/* Struct for players */
struct Player
{
	/* Default constructor for player one */
	Player()
	{
		player = sf::CircleShape(10.f);
		player.setFillColor(sf::Color::Green);
		x = 0;
		y = 0;
	};

	/* Contructor for enemy players */
	Player(int enemyID)
	{
		player = sf::CircleShape(10.f);
		player.setFillColor(sf::Color::Red);
		x = 0;
		y = 0;
		id = enemyID;
	}

	~Player()
	{
	};

	/* Method to update the player position */
	void SetPos(int xPos, int yPos)
	{
		x = xPos;
		y = yPos;
		player.setPosition(x+100,y+100);
	};

	sf::CircleShape player;
	int x = 1 , y = 1 , id = 0, seq = 0;
	int tempX = 0, tempY = 0;

};



class Client
{
	public:
		/* Structs & enumerators for sending/recieving messages */
		enum ObjectDesc
		{
			Human,
			NonHuman,
			Vehicle,
			StaticObject
		};

		enum ObjectForm
		{
			Cube,
			Sphere,
			Pyramid,
			Con
		};

		/* Struct that contains x,y pos for the player */
		struct Coordinate
		{
			int x;
			int y;
		};

		/* What type of message we send to server and what type of message we get from server */
		enum MsgType
		{
			Join, // Client joining game at server
			Leave, // Client leaving game
			Change, // Information to clients
			Event, // Information from clients to server
			TextMessage // Send text messages to one or all
		};

		/* MessageHead */
		struct MsgHead
		{
			unsigned int length; // Total length for whole message
			unsigned int seq_no; // Sequence number
			unsigned int id; // Client ID or 0;
			MsgType type; // Type of message
		};

		/* Predefined message for join */
		struct JoinMsg
		{
			MsgHead head;
			ObjectDesc desc;
			ObjectForm form;
			char name[MAXNAMELEN];
		};

		/* Use for leaving the server, set LeaveMsg.head->type to Leave */
		struct LeaveMsg
		{
			MsgHead head;
		};

		/* Events that can happen in the game */
		enum EventType
		{
			Move
		};

		/* Message to/from server with a event */
		struct EventMsg
		{
			MsgHead head; 
			EventType type;
		};

		/* MoveEvent  */
		struct MoveEvent
		{
			EventMsg event;
			Coordinate pos;
			Coordinate dir;
		};

		struct TextMessageMsg
		{
			MsgHead head;
			char text[1];
		};

		enum ChangeType
		{
			NewPlayer,
			PlayerLeave,
			NewPlayerPosition
		};

		// Included first in all Change messages struct ChangeMsg
		struct ChangeMsg
		{
			MsgHead head;
			ChangeType type;
		};

		struct NewPlayerMsg
		{
			ChangeMsg msg; //Change message header with new client id
			ObjectDesc desc;
			char name[MAXNAMELEN]; // nullterminated!, or empty
		};
		struct PlayerLeaveMsg
		{
			ChangeMsg msg; //Change message header with new client id
		};
		struct NewPlayerPositionMsg
		{
			ChangeMsg msg; //Change message header
			Coordinate pos; //New object position
			Coordinate dir; //New object direction
		};

		/* Contructor/Destructor */
		Client();
		~Client();

		/* Methods to communicate with server */
		void ConnectToServer( std::string ip, std::string port);
		void Listen();
		void Send(int xPos, int yPos);
		void Quit();
		void ThreadListener();

		/* Methods to get protected/private variables */
		Player& GetPlayer();
		std::vector<Player>& GetList();

	protected:
		int playerSeqNr = 0;
		Player player;
		std::vector<Player> playerList;
		std::vector<char> msgbuffer;


	private:

		SOCKET clientSocket = INVALID_SOCKET;
		std::thread listener;

		int errorCode;
		int buflen = DEFAULT_BUFLEN;
		char recieveBuff[DEFAULT_BUFLEN];
		bool hasConnected = false;
};

