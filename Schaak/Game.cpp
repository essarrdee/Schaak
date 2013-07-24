#include "Game.h"
#include <random>



Game::Game(void)
{
	chessSet = new ChessSet();
	board = new Board();
	doomedWanderer = new Piece();
	doomedWanderer->myType = chessSet->pieceTypes[1];
	doomedWanderer->myType->alterCover(doomedWanderer,board,1);
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
	doomedWanderer->myType->cooldown(doomedWanderer);
	if(doomedWanderer->energy > ENERGY_THRESHOLD)
	{
		doomedWanderer->energy -= ENERGY_THRESHOLD;
		doomedWanderer->myType->randomMove(doomedWanderer,board);
		board->updateBoardImage();
	}
}