#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include "Game.h"
//#include "MenuSystem.h"

#pragma once

// Class to create an SFML window and handle the game loop.
// Does not render any specific things - delegates this to the MenuSystem class

class Interface
{
public:
	Interface(void);
	~Interface(void);
	static sf::Vector2u windowSize; // win isn't public but its size must be
private:
	void init();
	void run();
	sf::RenderWindow win;
	//Game* game; // should be made a member of the MenuSystem unless there's a good reason.
	//MenuSystem* menu;
	bool done; // false until user exits
};

