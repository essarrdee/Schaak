#include "Game.h"
#include <random>



Game::Game(void)
{
	chessSet = new ChessSet();
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
	switch(e.type)
	{
	case sf::Event::MouseWheelMoved:
		board->zoom(e.mouseWheel);

	}
}
int Game::gameState()

{
    return 0;
}

void Game::simulate()
{
	board->alterPlayerCover(rand()%BOARD_SIZE_X,rand()%BOARD_SIZE_Y,rand()%3 - 1);
	board->alterEnemyCover(rand()%BOARD_SIZE_X,rand()%BOARD_SIZE_Y,rand()%3 - 1);
	board->updateBoardImage();
}