#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game : public sf::Drawable
{
public:
	Game(void);
	~Game(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void processEvent(sf::Event e);
	int gameState();
private:
	Board* board;
};

