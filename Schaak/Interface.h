#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include "Game.h"
//#include "MenuSystem.h"

#pragma once
class Interface
{
public:
	Interface(void);
	~Interface(void);
	static sf::Vector2u windowSize;
private:
	void init();
	void run();
	sf::RenderWindow win;
	//Game* game;
	//MenuSystem* menu;
	bool done;
};

