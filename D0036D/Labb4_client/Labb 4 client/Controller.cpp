#include "Controller.h"

Controller::Controller()
{
	
}

Controller::~Controller()
{

}


void Controller::InitView()
{
	view.InitView();
}

void Controller::Update()
{
	while (view.GetWindow()->isOpen())
	{
		sf::Event event;

		while (view.GetWindow()->pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{

				case sf::Keyboard::W:
					accY = -1;
					GetClient().Send(GetList()[0].x + accX, GetList()[0].y + accY);
					break;

				case sf::Keyboard::S:
					accY = 1;

					GetClient().Send(GetList()[0].x + accX, GetList()[0].y + accY);
					break;

				case sf::Keyboard::D:
					accX = 1;
					GetClient().Send(GetList()[0].x + accX, GetList()[0].y + accY);
					break;

				case sf::Keyboard::A:
					accX = -1;
					GetClient().Send(GetList()[0].x + accX, GetList()[0].y + accY);
					break;

				case sf::Keyboard::Escape:
					GetClient().Quit();
					view.CloseWindow();
					break;
				}
				break;
				
			case sf::Event::KeyReleased:
				accX = 0;
				accY = 0;
				break;
			}

		}
		Draw();
	}
}

Model& Controller::GetModel()
{
	return model;
}

Client& Controller::GetClient()
{
	return model.GetClient();
}

Player& Controller::GetPlayer()
{
	return model.GetPlayer();
}

std::vector<Player>& Controller::GetList()
{
	return model.GetList();
}

void Controller::Draw()
{
	view.GetWindow()->clear();
	for (int i = 0; i < GetList().size(); i++)
	{
		view.Draw(GetList().at(i).player);
	}
	view.GetWindow()->display();
}