
#include "Controller.h"
#include <iostream>

void main()
{

	Controller cont;
	std::string ip;
	std::string port;
	std::cout << "Please enter IP-address to connect to: ";
	std::cin >> ip;
	std::cout << "Please enter port: ";
	std::cin >> port;
	cont.GetModel().Connect(ip,port);
	cont.InitView();
	cont.Update();
	//cont.model.client.Quit();
	std::cin.get();

}