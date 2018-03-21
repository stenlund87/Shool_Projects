#pragma once
#include "Client.h"

class Model
{
	public:
		Model();
		~Model();

		/* Methods to get access to private objects*/
		Client& GetClient();
		Player& GetPlayer();
		std::vector<Player>& GetList();

		/* Methods to manipulate objects */
		void SetPos(int playerID, int xPos, int yPos);
		void Connect(std::string ipAdress, std::string port);
		void UpdatePos(int xPos, int yPos);

	private:
		Client client;

};