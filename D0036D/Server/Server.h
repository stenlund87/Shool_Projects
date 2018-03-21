#pragma once

#define NUM_THREADS 10
#define IP_ADRESS "130.240.40.24"
#define PORT_NO 5555


#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <vector>
#include "Messages.h"
#include "ThreadHelper.h"




class Server
{
    public:
        Server();
        ~Server();
        void StartServer();
        void SendUpdate(char buf[], int size);
        std::vector<ThreadHelper*>* GetThreads();
        void RemovePlayer(int id);
        void ShutDown();
		
		pthread_mutex_t lock;
		
    protected:

        unsigned int playerID;
        std::vector<int> clientSockets;
        int connectedClients;

    private:

        std::vector<ThreadHelper*> activeThreads;
        std::vector<pthread_t> threads;

        int socketfd;
        int clientFD;
        int idList[10];
		std::vector<int> idVector;

        char buffer[512];

};
