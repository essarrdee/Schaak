#include "Game.h"
#include "utilities.h"
#include <random>
#include "Interface.h"



Game::Game(void)
{
	chessSet = new ChessSet();
	board = new Board();
	pieces = new PieceManager();
	ticks = 0;
	paused = false;
	pauseStateChanged = true;
	mouseInWindow = true;
	lastMousePosition = sf::Vector2i(400,400); // TODO magic number, get it from some sensible variable
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
		switch(e.key.code)
		{
		case sf::Keyboard::Space:
			paused = !paused;
			pauseStateChanged = true;
			break;
		}
		break;
	case sf::Event::MouseMoved:
		lastMousePosition.x = e.mouseMove.x;
		lastMousePosition.y = e.mouseMove.y;
		break;
	case sf::Event::MouseLeft:
		mouseInWindow = false;
		break;
	case sf::Event::MouseEntered:
		mouseInWindow = true;
		break;
	}
}
int Game::gameState()

{
    return 0;
}

void Game::simulate()
{
	// TODO Magic numbers, put them in common.h
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		board->scroll(sf::Vector2f(0.f,1.8f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		board->scroll(sf::Vector2f(0.f,-1.8f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		board->scroll(sf::Vector2f(1.8f,0.f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		board->scroll(sf::Vector2f(-1.8f,0.f));
	if(mouseInWindow)
	{
		if(lastMousePosition.x < 40)
		{
			board->scroll(sf::Vector2f(1.8f,0.f));
		}
		else if(lastMousePosition.x > (signed)Interface::windowSize.x - 40)
		{
			board->scroll(sf::Vector2f(-1.8f,0.f));
		}
		if(lastMousePosition.y < 40)
		{
			board->scroll(sf::Vector2f(0.f,1.8f));
		}
		else if(lastMousePosition.y > (signed)Interface::windowSize.y - 40)
		{
			board->scroll(sf::Vector2f(0.f,-1.8f));
		}
	}
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
		p.alterCover(board,1);
		pieces->addPiece(&p);
	}

	for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
	{
		Piece* p = &*it;
		if(!p->dead)
		{
			p->cooldown();
			if(p->energy > ENERGY_THRESHOLD)
			{
				p->energy -= ENERGY_THRESHOLD;
				pieces->randomMove(p->id,board);
			}
		}
	}
	if(ticks%5 == 0)
	{
		board->updateBoardImage();
	}
}