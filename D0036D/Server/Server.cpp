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
	for(int i = 0; i< 10; i++)
	{
		this->idList[i] = i+4;
	}
	connectedClients = 0;
	pthread_mutex_init(&lock, NULL);
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
            if(connectedClients < 10)
            {				
                clientSockets.push_back(clientFD);
                connectedClients++;
				playerID = clientFD;
                //playerID = this->idList[index];
                index++;
				
				
				ThreadHelper* thread = new ThreadHelper(clientFD, this, playerID);
				activeThreads.push_back(thread);
				
				pthread_t newThread;
				//std::mutex activeThreads_mutex;
				pthread_create(&newThread, NULL, &ThreadStarter, &thread);
				threads.push_back(newThread);
				std::cout << "Threads are started!!!!" << std::endl;
            }



        }


     }
}


void Server::SendUpdate(char buf[], int size)
{
     int n;
     int client;
     for(int i = 0; i < clientSockets.size(); i++)
     {
        client = clientSockets[i];
        n = send(client, (void*)buf, size, 0);
		std::cout << "We are sending to client!" << std::endl;
		std::cout << "This is client " << client << std::endl;
        if (n < 0)
        {
            std::cout << "ERROR writing to socket" << std::endl;
            //exit(1);
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

