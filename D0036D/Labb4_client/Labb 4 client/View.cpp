#include "View.h"
#include <thread>

View::View()
{

}

View::~View()
{
	delete window;
	window = nullptr;
}

void View::InitView()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Blob Battle!!!");
}

void View::Draw(sf::CircleShape player)
{
	//std::this_thread::sleep_for(std::chrono::microseconds(1));
	window->draw(player);
}

void View::CloseWindow()
{
	window->close();
	exit(1);
}

sf::RenderWindow* View::GetWindow()
{
	return window;
}