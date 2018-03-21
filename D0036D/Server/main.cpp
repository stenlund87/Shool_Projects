//#include <iostream>
//#include "Server.h"

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
#include "Server.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    Server server;
    server.StartServer();
}
