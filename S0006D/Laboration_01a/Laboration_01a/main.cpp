
#include <iostream>
#include <string.h>
#include "Agent.h"
#include "EntityManager.h"
#include "MessageSender.h"

void main()
{
	Agent* ross = new Agent(1, "Ross");
	ross->SetColor(10);

	Agent* rachel = new Agent(1,"Rachel" ,20, 15);
	rachel->SetGains(10, 15, 20, 13);
	rachel->SetColor(11);

	Agent* joey = new Agent(3, "Joey", 40, 20);
	joey->SetGains(25, 18, 25, 10);
	joey->SetColor(12);

	Agent* chandler = new Agent(4, "Chandler", 25, 18);
	chandler->SetGains(18, 15, 20, 11);
	chandler->SetColor(13);

	while (true)
	{
		ross->Update();

		rachel->Update();
		joey->Update();
		chandler->Update();

		Send->SendDelayedMessages();
	}

	delete ross;
	delete rachel;
	delete joey;
	delete chandler;
	std::system("PAUSE");
}