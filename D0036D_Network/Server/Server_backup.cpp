#include "Server.h"
#include <mutex>

struct Helper
{
    ThreadHelper* th;
};

void* ThreadStarter(void* args)
{
    Helper* help = (Helper*)args;
    help->th->Recieve();
}

Server::Server()
{
	for(int i = 0; i<10; i++)
	{
		idVector.push_back(i+4);
		idList[i] = i+4;
	}
	connectedClients = 0;
}

Server::~Server()
{

}


void Server::StartServer()
{
     socklen_t clilen;

     struct sockaddr_in serv_addr, cli_addr;
     socketfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
     if (socketfd < 0)
     {
        std::cout << "ERROR opening socket" << std::endl;
        //exit(1);
     }
	 
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = 0;
     std::cout << serv_addr.sin_port << std::endl;

     if (bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
     {
        std::cout << "ERROR on binding" << std::endl;
        //exit(1);
     }
     socklen_t slen = sizeof(serv_addr);
     getsockname(socketfd,(struct sockaddr *) &serv_addr, &slen);
     std::cout << "This is the port that was bound: "<< ntohs(serv_addr.sin_port) << std::endl;

     listen(socketfd,5);
     int index = 0;

     while(true)
     {
        clilen = sizeof(cli_addr);

        clientFD = accept(socketfd, (struct sockaddr *) &cli_addr, &clilen);

        std::cout << clientFD << std::endl;

        if (clientFD < 0)
        {
            std::cout << "ERROR on accept" << std::endl;
        }
        else
        {
            std::cout << "Connection Successful" << std::endl;
            if(index < 10)
            {
                clientSockets.push_back(clientFD);
                playerID = idList[index];
				connectedClients++;
                index++;
				ThreadHelper* thread = new ThreadHelper(clientFD, this, playerID);
				activeThreads.push_back(thread);
				
				pthread_t newThread;
				std::mutex activeThreads_mutex;
				pthread_create(&newThread, NULL, &ThreadStarter, &thread);
				threads.push_back(newThread);
				std::cout << "Threads are started!!!!" << std::endl;
            }



        }


     }
}


char* Server::GetBuffer()
{
    return buffer;
}




void Server::SendUpdate(char buf[], int size, int sender)
{
	std::cout << "We are in the SendUpdate method" << std::endl;
     int n;
     int client;
     for(int i = 0; i < connectedClients; i++)
     {
		std::cout << "We are in the loop" << std::endl;
        client = clientSockets.at(i);
		std::cout << "We are sending to client: " << client << std::endl;
        n = send(client, (void*)buf, size, 0);
        if (n < 0)
        {
            std::cout << "ERROR writing to socket" << std::endl;
        }
     }
}

void Server::SendJoin(char buff[], int size, int senderSocket)
{
	std::cout << "We are in the SendJoin method" << std::endl;
    int n;
    int client;
    for(int i = 0; i < connectedClients; i++)
    {
        client = clientSockets.at(i);
		if(client != senderSocket)
		{
			std::cout << "Msg sent to: " << client << std::endl;
			n = send(client, (void*)buff, size, 0);
			if (n < 0)
			{
				std::cout << "ERROR writing to socket" << std::endl;

			}
		}

    }
}


std::vector<ThreadHelper*>* Server::GetThreads()
{
    return &activeThreads;
}

void Server::ShutDown()
{
     close(clientFD);
     close(socketfd);
}

unsigned int Server::GetPlayerID()
{
    return playerID;
}

void Server::RemovePlayer(int id)
{

    for(int i = 0; i< activeThreads.size(); i++)
    {
        if(activeThreads.at(i)->GetID() == id)
        {
			pthread_mutex_lock(&lock);
           (void)pthread_join(threads[i],NULL);
            activeThreads.erase(activeThreads.begin()+i);
            close(clientSockets.at(i));
            clientSockets.erase(clientSockets.begin()+i);
            std::cout << "Bye bye" <<std::endl;
            connectedClients--;
			pthread_mutex_unlock(&lock);
            break;
        }
    }

}

