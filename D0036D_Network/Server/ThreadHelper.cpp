#include "ThreadHelper.h"
#include "Server.h"
#include <strings.h>
#include <iostream>





ThreadHelper::ThreadHelper(int socket, Server* serv, int ID)
{
    clientSocket = socket;
    server = serv;
    xPos = -100;
    yPos = -100;
    clientID = ID;
	buflen = 512;
	seq = 0;
}

ThreadHelper::~ThreadHelper()
{
    //dtor
}

void ThreadHelper::Recieve()
{
    int n;
    char clientBuffer[512];
	std::vector<char> msgbuffer;
    do
    {
        bzero(clientBuffer,512);
		std::cout << clientSocket << std::endl;
		std::cout << "Listening to package" << std::endl;
        n = recv(clientSocket,clientBuffer, buflen,0);
        if (n < 0)
        {
            std::cout << "ERROR reading from socket" << std::endl;
			close(clientSocket);
			
			ChangeMsg leave;
			leave.head.type = Change;
			leave.head.id = clientID;

			leave.type = PlayerLeave;
			
			leave.head.length = sizeof(leave);
			
			int msgSize = sizeof(leave);
			char sendBuff[msgSize];
			memcpy((void*)sendBuff, (void*)&leave, msgSize);

			server->SendUpdate(sendBuff, msgSize);		
			
			server->RemovePlayer(GetID());
			break;			
        }
		else if(n > 0)
		{
			MsgHead* msghead;
			msghead = (MsgHead*)clientBuffer;

			int pID = msghead->id;
			for (int i = 0; i < n; i++)
			{
				msgbuffer.push_back(clientBuffer[i]);
			}
			while (msgbuffer.size() >= sizeof(MsgHead))
			{
				char tempHead[sizeof(MsgHead)];
				for (unsigned int i = 0; i < sizeof(MsgHead); i++)
				{
					tempHead[i] = msgbuffer[i];
				}
				MsgHead* msghead;
				msghead = (MsgHead*)tempHead;
				
				if (msgbuffer.size() >= msghead->length && msghead->length > 0)
				{
					if(msghead->type == Join)
					{				
						std::cout << "We are getting a join message!" << std::endl;
						JoinMsg join;
						join.head.id = this->clientID;
						join.head.type = Join;
						join.head.length = sizeof(join);						
						std::cout << "This is the ID for the client: " << this->clientID << std::endl;
						
						char sendBuff[sizeof(join)];
						memcpy((void*)sendBuff, (void*)&join, sizeof(join));
						
						send(this->clientSocket, (void*)sendBuff, sizeof(join), 0);
						
						std::cout << "Join Message sent!" << std::endl;		
						//msgbuffer.erase(msgbuffer.begin(),msgbuffer.begin() + msghead->length);
						
						//Message to all other clients to tell them that a new player has joined
						ChangeMsg change;
						change.head.type = Change;
						change.head.id = this->clientID;
						change.type = NewPlayer;			
						int msgSize = sizeof(change);
						change.head.length = msgSize;
						char changeBuff[msgSize];
						memcpy((void*)changeBuff, (void*)&change, msgSize);
						server->SendUpdate(changeBuff, msgSize);
						std::cout << "We are sending ChangeMsg" << std::endl;
						
						//Set position for the new player
						NewPlayerPositionMsg nppm;
						nppm.msg.head.type = Change;
						nppm.msg.head.id = this->clientID;
						nppm.pos.x = -100;
						nppm.pos.y = -100;
						nppm.msg.type = NewPlayerPosition;
						nppm.msg.head.length = sizeof(nppm);
						
						changeBuff[sizeof(nppm)];
						memcpy((void*)changeBuff, (void*)&nppm, sizeof(nppm));
						std::cout << "We are sending NewPlayerPositionMsg" << std::endl;
						server->SendUpdate(changeBuff, sizeof(nppm));
						
						msgbuffer.erase(msgbuffer.begin(),msgbuffer.begin() + msghead->length);
						
						for(unsigned int p =0; p<server->GetThreads()->size(); p++)
						{
							if(server->GetThreads()->at(p)->clientID == this->clientID)
							{
								continue;
							}
							ChangeMsg oldPlayer;
							oldPlayer.head.type = Change;
							oldPlayer.head.id = server->GetThreads()->at(p)->clientID;
							oldPlayer.type = NewPlayer;			
							int msgSize = sizeof(oldPlayer);
							oldPlayer.head.length = msgSize;
							char changeBuff[msgSize];
							memcpy((void*)changeBuff, (void*)&oldPlayer, msgSize);
							send(this->clientSocket, (void*)changeBuff, sizeof(oldPlayer), 0);
							std::cout << "We are sending ChangeMsg" << std::endl;
							
							//Send the position of an old player
							NewPlayerPositionMsg oldPlayerPosition;
							oldPlayerPosition.msg.head.type = Change;
							oldPlayerPosition.msg.head.id = server->GetThreads()->at(p)->clientID;
							oldPlayerPosition.pos.x = server->GetThreads()->at(p)->xPos;
							oldPlayerPosition.pos.y = server->GetThreads()->at(p)->yPos;
							oldPlayerPosition.msg.type = NewPlayerPosition;
							oldPlayerPosition.msg.head.length = sizeof(nppm);
							
							changeBuff[sizeof(oldPlayerPosition)];
							memcpy((void*)changeBuff, (void*)&oldPlayerPosition, sizeof(oldPlayerPosition));
							
							send(this->clientSocket, (void*)changeBuff, sizeof(oldPlayerPosition), 0);
						}
					}

					else if(msghead->type == Event)
					{
						EventMsg* event;
						event = (EventMsg*)&msgbuffer[0];

						if(event->type == Move)
						{
							std::cout << "In move" << std::endl;
							MoveEvent* move;
							move = (MoveEvent*)&msgbuffer[0];
							int pX = move->pos.x;
							int pY = move->pos.y;
							msgbuffer.erase(msgbuffer.begin(),msgbuffer.begin() + msghead->length);
							std::cout << "This is the clientID: " << msghead->id << std::endl;

							for(unsigned int i =0; i<server->GetThreads()->size(); i++)
							{
								bool moveOK = false;     
								pthread_mutex_lock(&server->lock) //<<Locking because we are going to change values in the array
								if(server->GetThreads()->at(i)->clientID == pID && pX > -101 && pX < 101 && pY > -101 && pY <101)
								{
									int deltaX = pX - server->GetThreads()->at(i)->xPos;
									int deltaY = pY - server->GetThreads()->at(i)->yPos;
									
									bool moveXOK;
									bool moveYOK;
													
									for(unsigned int k = 0; k < server->GetThreads()->size(); k++)
									{
										bool dX = deltaX > 0 || deltaX <0;
										bool dY = deltaY>0 || deltaY <0;

										if(dX)
										{
											moveXOK = server->GetThreads()->at(k)->xPos != server->GetThreads()->at(i)->xPos+deltaX;
										}
										else if(dY)
										{
											moveYOK = server->GetThreads()->at(k)->yPos != server->GetThreads()->at(i)->yPos+deltaY;
										}
										
										if(k+1 == server->GetThreads()->size() && moveXOK || moveYOK)
										{
											moveOK = true;
										}

										if(moveOK)
										{
											
											server->GetThreads()->at(i)->xPos = pX;
											server->GetThreads()->at(i)->yPos = pY;										
											server->GetThreads()->at(i)->seq = move->event.head.seq_no;
											
											pthread_mutex_unlock(&server->lock); //<< Unlocking
											
											NewPlayerPositionMsg change;
											change.msg.head.type = Change;
											change.msg.type = NewPlayerPosition;
											change.msg.head.id = pID;
											change.pos.x = pX;
											change.pos.y = pY;
											
											std::cout << "We are sending the player to x: " << pX << " and y: " << pY << std::endl; 
											
											change.msg.head.seq_no = server->GetThreads()->at(i)->seq;
											change.msg.head.length = sizeof(change);
											int msgSize = sizeof(change);
											char sendBuff[msgSize];
											memcpy((void*)sendBuff, (void*)&change, msgSize);
											
											std::cout << "We are about to send!" << std::endl;
											server->SendUpdate(sendBuff, msgSize);
											std::cout << "Sending move" << std::endl;
											
											
										}
									} 
								}
							}
						}
					}
					
					else if(msghead->type == Leave)
					{
						std::cout << "Recieved Leave message! Sending to others" << std::endl;
						//Recieved a Leave message, relaying the info to the rest of the players
						ChangeMsg leave;
						leave.head.type = Change;
						leave.head.id = clientID;

						leave.type = PlayerLeave;
						
						leave.head.length = sizeof(leave);
						
						int msgSize = sizeof(leave);
						char sendBuff[msgSize];
						memcpy((void*)sendBuff, (void*)&leave, msgSize);

						server->SendUpdate(sendBuff, msgSize);
						
						server->RemovePlayer(GetID());
						break;
						std::cout << "We are getting a leave!" << std::endl;
						msgbuffer.erase(msgbuffer.begin(),msgbuffer.begin() + msghead->length);
						
					}		
				}
				
			}
		}
		
	}
	while(n>0);
	
}


int ThreadHelper::GetID()
{
    return clientID;
}

