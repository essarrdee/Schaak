#include "Game.h"



Game::Game(void)
{
	board = new Board();
}


Game::~Game(void)
{
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*board);
}

void Game::processEvent(sf::Event e)
{

}
int Game::gameState()

{
    return 0;
}