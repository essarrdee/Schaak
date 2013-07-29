#include "Game.h"
#include "utilities.h"
#include <random>
#include "Interface.h"



Game::Game(void)
{
	behaviours = new BehaviourManager();
	chessSet = new ChessSet(behaviours);
	board = new Board();
	pieces = new PieceManager();
	ticks = 0;
	paused = false;
	pauseStateChanged = true;
	mouseInWindow = true;
	lastMousePosition = sf::Vector2i(400,400); // TODO magic number, get it from some sensible variable
	whiteControlling = false;
	blackControlling = false;
	selectingWithLeftButton = false;
	selectingWithRightButton = false;
	selectionBoxShape.setFillColor(sf::Color::Transparent);
	selectionBoxShape.setOutlineThickness(2.0);
}


Game::~Game(void)
{
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*board);
	drawPieces(target,states);
	if(selectingWithLeftButton || selectingWithRightButton)
		target.draw(selectionBoxShape);
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
					if(p->myType == pt && p->isBlack == blackPieces)
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
		case sf::Keyboard::F1:
			whiteControlling = true;
			blackControlling = false;
			break;
		case sf::Keyboard::F2:
			blackControlling = true;
			whiteControlling = false;
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
	case sf::Event::MouseButtonPressed:
		if(e.mouseButton.button == sf::Mouse::Left)
		{
			selectingWithLeftButton = true;
			selectingWithRightButton = false;
		}
		else if(e.mouseButton.button == sf::Mouse::Right)
		{
			selectingWithRightButton = true;
			selectingWithLeftButton = false;
		}
		if(selectingWithLeftButton || selectingWithRightButton)
		{
			sf::Vector2i screenPosition(e.mouseButton.x,e.mouseButton.y);
			selectionBoxStart = ((sf::Vector2f)screenPosition-board->boardSprite.getPosition())/(float)board->magnificationLevel();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if((e.mouseButton.button == sf::Mouse::Left && selectingWithLeftButton) ||
			(e.mouseButton.button == sf::Mouse::Right && selectingWithRightButton))
		{
			sf::Vector2i screenPosition(e.mouseButton.x,e.mouseButton.y);
			sf::Vector2f selectionBoxEnd = ((sf::Vector2f)screenPosition-board->boardSprite.getPosition())/(float)board->magnificationLevel();
			pieces->drawBox(selectionBoxStart,selectionBoxEnd,blackControlling,e.mouseButton.button == sf::Mouse::Right);
		}
		if(e.mouseButton.button == sf::Mouse::Left)
			selectingWithLeftButton = false;
		if(e.mouseButton.button == sf::Mouse::Right)
			selectingWithRightButton = false;
		break;

	//	{
	//		selectingWithLeftButton = false;
	//	}
	//	else if(e.mouseButton.button == sf::Mouse::Right)
	//	{
	//		selectingWithRightButton = false;
	//	}
	//	if(selectingWithLeftButton || selectingWithRightButton)
	//	{
	//		sf::Vector2i screenPosition(e.mouseButton.x,e.mouseButton.y);
	//		selectionBoxStart = ((sf::Vector2f)screenPosition-board->boardSprite.getPosition())/(float)board->magnificationLevel();
	//	}
	//	break;
	}
}
int Game::gameState()

{
    return 0;
}

void Game::simulate()
{
	sf::Vector2f SelectionBoxStartScreenCoords = selectionBoxStart*(float)board->magnificationLevel()+board->boardSprite.getPosition();
	selectionBoxShape.setPosition(SelectionBoxStartScreenCoords);
	selectionBoxShape.setSize((sf::Vector2f)sf::Mouse::getPosition()-SelectionBoxStartScreenCoords);
	if(selectingWithLeftButton)
		selectionBoxShape.setOutlineColor(sf::Color::Cyan);
	else if(selectingWithRightButton)
		selectionBoxShape.setOutlineColor(sf::Color::Red);

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

	if(ticks % 10 == 0)
	{
		Piece p;

		p.position.x = rand() % BOARD_SIZE_X;
		p.position.y = rand() % BOARD_SIZE_Y;
		int c=0;
		while(!nullPiece(board->occupants[p.position.x][p.position.y]))
		{
			c++;
			if(c >= 10)
				break;
			p.position.x = rand() % BOARD_SIZE_X;
			p.position.y = rand() % BOARD_SIZE_Y;
		}
		if(c < 10)
		{
			p.myType = chessSet->pieceTypes[rand()%6];
			p.isBlack = (rand()%2)==0;
			p.alterCover(board,1);
			p.dead = false;
			pieces->addPiece(&p);
		}
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
				pieces->AIMove(p->id,board);
			}
		}
	}
	if(ticks%5 == 0)
	{
		board->updateBoardImage();
	}
}