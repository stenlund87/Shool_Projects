#pragma once
#include "Client.h"
#include <exception>
#include <algorithm>
#include <limits>

Client::Client()
{
}

Client::~Client()
{
	clientSocket = INVALID_SOCKET;
	listener.~thread();

}

void Client::ConnectToServer(std::string ip, std::string port)
{
	WSADATA wsaData;
	int errorCode;

	const char* portNumber = port.c_str();

	errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (errorCode != 0)
	{
		printf("Startup failed: %d\n", errorCode);
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	SecureZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	const char* connectTo = ip.c_str();

	errorCode = getaddrinfo(connectTo, portNumber, &hints, &result);
	if (errorCode != 0)
	{
		std::printf("getaddrinfo failed: %d\n", errorCode);
		WSACleanup();
	}

	ptr = result;

	this->clientSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (this->clientSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
	}

	errorCode = connect(this->clientSocket, ptr->ai_addr, ptr->ai_addrlen);

	if (errorCode == SOCKET_ERROR)
	{
		closesocket(this->clientSocket);
		this->clientSocket = INVALID_SOCKET;
	}
	freeaddrinfo(result);

	if (this->clientSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to the server!\n");
		int c;
		std::cout << "Please check that both IP and port is correct!" << std::endl;
		std::cout << "Please press any number and then press enter to quit application" << std::endl;
		std::cin >> c;
		WSACleanup();
	}

	JoinMsg jMsg;
	int buflen = DEFAULT_BUFLEN;

	char sendBuff[sizeof(jMsg)];
	char recieveBuff[DEFAULT_BUFLEN];

	jMsg.head.id = 0;
	jMsg.head.length = sizeof(jMsg);
	jMsg.head.type = Join;

	memcpy((void*)sendBuff, (void*)&jMsg, sizeof(jMsg));

	errorCode = send(this->clientSocket, sendBuff, sizeof(sendBuff), 0);
	if (errorCode == SOCKET_ERROR)
	{
		printf("Send failed: %d\n", WSAGetLastError());
		closesocket(this->clientSocket);
		WSACleanup();
	}
	printf("Bytes Sent: %ld\n", errorCode);
	hasConnected = true;
	listener = std::thread(&Client::ThreadListener, this);
}


void Client::Listen()
{
	do
	{
		std::cout << "We are recieving once again" << std::endl;
		errorCode = recv(this->clientSocket, recieveBuff, buflen, 0);
		if (errorCode > 0)
		{
			printf("Bytes received: %d\n", errorCode);

			for (int i = 0; i < errorCode; i++)
			{
				msgbuffer.push_back(recieveBuff[i]);
			}
			while (msgbuffer.size() >= sizeof(MsgHead))
			{
				std::cout << "We are in while" << std::endl;

				char tempHead[sizeof(MsgHead)];
				for (unsigned int i = 0; i < sizeof(MsgHead); i++)
				{
					tempHead[i] = msgbuffer[i];
				}
				MsgHead* msghead;
				msghead = (MsgHead*)tempHead;
			
				if (msgbuffer.size() >= msghead->length && msghead->length > 0)
				{
					std::cout << "If cleared!!!!" << std::endl;
					if (msghead->type == Join)
					{
						std::cout << "We are getting a join message with id" << msghead->id << std::endl;
						JoinMsg* join;
						join = (JoinMsg*)recieveBuff;
						Player self;
						self.id = msghead->id;

						playerList.push_back(self);

					}

					if (msghead->type == Change)
					{
						std::cout << "We are in change if" << std::endl;
						ChangeMsg* change;
						change = (ChangeMsg*)&msgbuffer[0];
						if (change->type == NewPlayerPosition)
						{
							std::cout << "We are getting a new position message" << std::endl;
							NewPlayerPositionMsg* np;

							np = (NewPlayerPositionMsg*)&msgbuffer[0];
							for (int i = 0; i < playerList.size(); i++)
							{
								std::cout << "This is player ID "<<playerList[i].id << std::endl;
								std::cout << "This is the msg head ID " << np->msg.head.id << std::endl;
								if (playerList[i].id == np->msg.head.id)
								{
									playerList[i].SetPos(np->pos.x, np->pos.y);
									std::cout << "We are setting position for player " << i << "to x " << np->pos.x << "y " << np->pos.y  << std::endl;

								}
								//else if (playerList[i].id != np->msg.head.id  && i == playerList.size() - 1 && playerList[0].id != np->msg.head.id)
								//{
								//	std::cout << "The player dont exist...Adding!!!!" << std::endl;
								//	int eID = np->msg.head.id;
								//	Player newPlayer(eID);
								//	playerList.push_back(newPlayer);
								//}
							}
						}

						else if (change->type == NewPlayer && playerList[0].id != msghead->id)
						{
							std::cout << "We are getting a new player message" << std::endl;
							NewPlayerMsg* npm;
							npm = (NewPlayerMsg*)&msgbuffer[0];
							int id = npm->msg.head.id;
							Player newPlayer(id);
							playerList.push_back(newPlayer);
						}
						else if (change->type == PlayerLeave)
						{
							std::cout << "We are getting a Leave message!" << std::endl;
							int id = change->head.id;
							for (int i = 0; i < playerList.size(); i++)
							{
								if (playerList[i].id == id)
								{
									playerList.erase(playerList.begin() + i);
								}
							}
						}
						//std::cout << "Getting change from server!!!!" << std::endl;
					}
					msgbuffer.erase(msgbuffer.begin(), msgbuffer.begin() + msghead->length);
				}
				else
				{
					break;
				}
				
			}
		}

		else if (errorCode == 0)
		{
			printf("Connection closed\n");
		}

		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
		
	}
	while (errorCode > 0);
	{
		exit(1);
	}
}

void Client::Send(int xPos, int yPos)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	MoveEvent msg;
	msg.event.type = Move;
	msg.event.head.type = Event;
	msg.event.head.id = playerList[0].id;
	msg.event.head.seq_no = playerList[0].seq;
	msg.event.head.length = sizeof(msg);
	msg.pos.x = xPos;
	msg.pos.y = yPos;

	char sendBuff[sizeof(msg)];

	memcpy((void*)sendBuff, (void*)&msg, sizeof(msg));
	errorCode = send(this->clientSocket, sendBuff, sizeof(sendBuff), 0);
	if (errorCode == SOCKET_ERROR)
	{
		printf("Send failed: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
	}
	printf("Bytes Sent: %ld\n", errorCode);
	playerList[0].seq += 1;
}


void Client::Quit()
{
	if (hasConnected)
	{
		int code;
		LeaveMsg leave;
		leave.head.type = Leave;
		leave.head.id = playerList[0].id;
		leave.head.length = sizeof(leave);

		int buflen = DEFAULT_BUFLEN;
		char sendBuff[sizeof(leave)];
		char recieveBuff[DEFAULT_BUFLEN];
		memcpy((void*)sendBuff, (void*)&leave, sizeof(leave));
		code = send(clientSocket, sendBuff, sizeof(sendBuff), 0);

		closesocket(clientSocket);
		WSACleanup();
	}
}


Player& Client::GetPlayer()
{
	return player;
}

std::vector<Player>& Client::GetList()
{
	return playerList;
}

void Client::ThreadListener()
{
	while (true)
	{
		Listen();
	}
}




