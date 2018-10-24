#include "Model.h"

Model::Model()
{
}

Model::~Model()
{

}

Client& Model::GetClient()
{
	return client;
}

Player& Model::GetPlayer()
{
	return client.GetPlayer();
}

std::vector<Player>& Model::GetList()
{
	return client.GetList();
}


void Model::SetPos(int playerID, int xPos, int yPos)
{
	for (int i = 0; i < GetList().size(); i++)
	{
		if (GetList()[i].id == playerID)
		{
			GetList()[i].SetPos(xPos, yPos);
		}
	}
}


void Model::Connect(std::string port, std::string ip)
{
	client.ConnectToServer(port, ip);
}

void Model::UpdatePos(int xPos, int yPos)
{
	GetPlayer().SetPos(xPos, yPos);
}