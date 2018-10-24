#pragma once
#include <SFML/Graphics.hpp>
#include "View.h"
#include "Model.h"
#include "Client.h"

class Controller
{
	public:
		Controller();
		~Controller();
		
		void InitView();
		void Update();
		Model& GetModel();
		Client& GetClient();
		Player& GetPlayer();
		std::vector<Player>& GetList();
		void Draw();

	private:
		Model model;
		View view;

		int accX, accY;
};