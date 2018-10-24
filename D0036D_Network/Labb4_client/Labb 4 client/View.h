#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class View
{
	public:
		View();
		~View();
		
		void InitView();
		void Draw(sf::CircleShape player);
		void CloseWindow();
		sf::RenderWindow* GetWindow();

	private:
		sf::RenderWindow* window;

};
