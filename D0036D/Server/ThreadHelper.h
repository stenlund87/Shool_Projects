#ifndef THREADHELPER_H
#define THREADHELPER_H

#define DEFAULT_BUFLEN 512


class Server;

class ThreadHelper
{
    public:
        ThreadHelper(int socket, Server* serv, int ID);
        virtual ~ThreadHelper();
        void Recieve();
        void UpdatePosition();
        int GetID();


    protected:
		Server* server;
    private:
        int clientSocket;
		int xPos;
		int yPos;		
		int clientID;
		int seq;
        int buflen;
        
};

#endif // THREADHELPER_H
