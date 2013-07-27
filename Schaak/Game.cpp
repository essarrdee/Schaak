#include "Game.h"
#include "utilities.h"
#include <random>



Game::Game(void)
{
	chessSet = new ChessSet();
	board = new Board();
	pieces = new PieceManager();
	ticks = 0;
	paused = false;
	pauseStateChanged = true;
}


Game::~Game(void)
{
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*board);
	drawPieces(target,states);
}
void Game::drawPieces(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect viewRect = board->visibleArea();
	for(auto ptit = chessSet->pieceTypes.begin(); ptit != chessSet->pieceTypes.end(); ++ptit)
	{
		for(int i = 0; i < 2; i++)
		{
			bool blackPieces = (i == 0);
			PieceType* pt = *ptit;
			pieces->piecesSprite.setTextureRect(pt->spriteLocation(board->magnificationCode,blackPieces));
			for (auto pit = pieces->pieces.begin(); pit != pieces->pieces.end(); ++pit)
			{
				Piece* p = &(*pit);
				if(!p->dead)
				{
					if(p->myType == pt && p->playerOwned == blackPieces)
					{
						sf::FloatRect r((sf::Vector2f)p->position,(sf::Vector2f)sf::Vector2i(board->magnificationLevel(),board->magnificationLevel()));
						if(r.intersects(viewRect)) // does r intersect the visible rect of the board?
						{
							pieces->piecesSprite.setPosition((sf::Vector2f)(p->position*sf::Vector2i(board->magnificationLevel(),board->magnificationLevel())) + board->boardSprite.getPosition());
							target.draw(pieces->piecesSprite);
						}

					}
				}
			}
		}
	}
}

void Game::processEvent(sf::Event e)
{
	switch(e.type)
	{
	case sf::Event::MouseWheelMoved:
		board->zoom(e.mouseWheel);
		break;
	case sf::Event::KeyPressed:
		if(e.key.code = sf::Keyboard::Space)
		{
			paused = !paused;
			pauseStateChanged = true;
		}
		break;
	}
}
int Game::gameState()

{
    return 0;
}

void Game::simulate()
{
	if(paused)
	{
		if(pauseStateChanged)
		{
			board->updateBoardImage();
			pauseStateChanged = false;
		}
		return;
	}
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