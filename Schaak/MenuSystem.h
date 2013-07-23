#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"

// Renders all menus, interface objects, HUD, and delegates map viewport rendering

class MenuSystem : public sf::Drawable
{
public:
	enum MenuState
	{ // if we have different screen states, put them here
		splash,
		game,
	};
	//int splashNum;
	MenuSystem(void);
	~MenuSystem(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void processEvent(sf::Event e);
private:
	void startGame();
	MenuState state;
	Game* schaak; // holds all game state and renders map.
};

