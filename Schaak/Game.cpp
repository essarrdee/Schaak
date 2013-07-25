#include "Game.h"
#include <random>



Game::Game(void)
{
	chessSet = new ChessSet();
	board = new Board();
	pieces = new PieceManager();
	ticks = 0;
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
	ticks++;

	if(ticks % 20 == 0)
	{
		Piece p;
		p.dead = false;
		p.myType = chessSet->pieceTypes[(ticks/60)%6];
		p.playerOwned = ((ticks/60)%2)==0;
		p.position.x = ((ticks/60) * 1033) % BOARD_SIZE_X;
		p.position.y = ((ticks/60) * 43) % BOARD_SIZE_Y;
		p.myType->alterCover(&p,board,1);
		pieces->addPiece(&p);
	}

	for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
	{
		Piece* p = &*it;
		if(!p->dead)
		{
			p->myType->cooldown(p);
			if(p->energy > ENERGY_THRESHOLD)
			{
				p->energy -= ENERGY_THRESHOLD;
				p->myType->randomMove(p,board);
			}
		}
	}
	if(ticks%5 == 0)
	{
		board->updateBoardImage();
	}
}