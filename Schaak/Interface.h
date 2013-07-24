#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MenuSystem.h"

// Class to create an SFML window and handle the game loop.
// Does not render any specific things - delegates this to the MenuSystem class

class Interface
{
public:
	Interface(void);
	~Interface(void);
	static sf::Vector2u windowSize; // win isn't public but its size must be
	// TODO make windowSize a public get, only Interface needs to write to it
private:
	void init();
	void run();
	sf::RenderWindow win;
	MenuSystem* menu;
	bool done; // false until user exits
	sf::Clock fpsClock;
	int framesThisSecond;
	float framesPerSecond;
	void calculateFPS();
};

