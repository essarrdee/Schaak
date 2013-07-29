#include "Game.h"
#include "utilities.h"
#include <random>
#include <iostream>
#include <fstream>
#include "Interface.h"
#include "Logger.h"



Game::Game(void)
{
	behaviours = new BehaviourManager();
	chessSet = new ChessSet(behaviours);
	board = new Board();
	pieces = new PieceManager();
	ticks = 0;
	realTicks = 0;
	paused = false;
	pauseStateChanged = true;
	mouseInWindow = true;
	lastMousePosition = sf::Vector2i(400,400); // TODO magic number, get it from some sensible variable
	blackControlling = false;
	selectingWithLeftButton = false;
	selectingWithRightButton = false;
	selectionBoxShape.setFillColor(sf::Color::Transparent);
	selectionBoxShape.setOutlineThickness(2.0);
	if(!defaultFont.loadFromFile(DEFAULT_FONT_PATH))
	{
		LERR("Could not load font ");
		LAPPEND(DEFAULT_FONT_PATH);
	}
	whiteCount.setPosition(0.f,560.f);
	blackCount.setPosition(0.f,600.f);
	moneyText.setPosition(0.f,640.f);
	whiteCount.setColor(sf::Color::Black);
	blackCount.setColor(sf::Color::Black);
	moneyText.setColor(sf::Color::Black);
	whiteCount.setFont(defaultFont);
	blackCount.setFont(defaultFont);
	moneyText.setFont(defaultFont);
	whiteCount.setCharacterSize(18);
	blackCount.setCharacterSize(18);
	moneyText.setCharacterSize(18);
	
	interfaceTexture.loadFromFile(IMAGE_PATH+"Interface.png");
	interfaceSprite.setTexture(interfaceTexture);
	interfaceSprite.setPosition(0.f,0.f);

	blackMoney = 0;
	whiteMoney = 0;

	std::ifstream f(RESOURCE_PATH+"buttons");
	while(f.good())
	{
		sf::IntRect r;
		f >> r.left >> r.top >> r.width >> r.height;
		buttonLocations.push_back(r);
		sf::RectangleShape rs;
		rs.setPosition((sf::Vector2f)sf::Vector2i(r.left,r.top));
		rs.setSize((sf::Vector2f)sf::Vector2i(r.width,r.height));
		rs.setFillColor(sf::Color::Transparent);
		buttons.push_back(rs);
		std::string name;
		f >> name;
		buttonNames.push_back(name);
	}
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
	target.draw(interfaceSprite);
	target.draw(blackCount);
	target.draw(whiteCount);
	target.draw(moneyText);
	for(auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		target.draw(*it);
	}
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
						if(p->selected && p->isBlack == blackControlling)
						{
							if(realTicks%48 < 12)
								continue;
						}
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

void Game::switchControl()
{
	blackControlling = !blackControlling;
	blackCount.setColor(blackCount.getColor() == sf::Color::Black ? sf::Color::White : sf::Color::Black);
	whiteCount.setColor(whiteCount.getColor() == sf::Color::Black ? sf::Color::White : sf::Color::Black);
	moneyText.setColor(moneyText.getColor() == sf::Color::Black ? sf::Color::White : sf::Color::Black);
			
	interfaceSprite.setTextureRect(sf::IntRect(sf::Vector2i(blackControlling?WINDOW_MIN_WIDTH : 0,0),sf::Vector2i(WINDOW_MIN_WIDTH,WINDOW_MIN_WIDTH)));
	board->blackControlling = blackControlling;
	for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
	{
		if(!(*it).dead)
		{
			(*it).alterCover(board,-1);
			(*it).alterCover(board,1);
		}
	}
	board->updateBoardImage();
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
		case sf::Keyboard::Tab:
			switchControl();
			break;
		case sf::Keyboard::Delete:
			{
				for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
				{
					if((*it).selected && !(*it).dead && (*it).isBlack == blackControlling)
					{
						if((*it).myType->name == "Pawn")
						{
							blackControlling ? blackMoney++ : whiteMoney++;
							pieces->killPiece((*it).id,board);
						}
					}
				}
			}
		}
		break;
	case sf::Event::MouseMoved:
		lastMousePosition.x = e.mouseMove.x;
		lastMousePosition.y = e.mouseMove.y;
		for(unsigned int i=0; i < buttonLocations.size(); i++)
		{
			if(buttonLocations[i].contains(lastMousePosition))
				buttons[i].setFillColor(sf::Color(0,128,128,128));
			else
				buttons[i].setFillColor(sf::Color::Transparent);
		}
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
			bool clickedButton = false;
			for(unsigned int i=0; i<buttons.size(); i++)
			{
				if(buttons[i].getFillColor() != sf::Color::Transparent)
				{
					clickedButton = true;
					std::string bName = buttonNames[i];
					if(bName == "select_all")
					{
						pieces->drawBox(sf::Vector2f(0.f,0.f),sf::Vector2f(BOARD_SIZE),blackControlling,false);
					}
					else if(bName == "switch_control")
					{
						switchControl();
					}
					else if(bName == "select_king")
					{
						for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
							if(!(*it).dead && (*it).isBlack == blackControlling)
							{
								if((*it).myType->name == "King")
								{
									if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && !(*it).selected)
										continue;
									(*it).selected = true;
								}
								else
									(*it).selected = false;
							}
					}
					else if(bName == "select_queen")
					{
						for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
							if(!(*it).dead && (*it).isBlack == blackControlling)
							{
								if((*it).myType->name == "Queen")
								{
									if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && !(*it).selected)
										continue;
									(*it).selected = true;
								}
								else
									(*it).selected = false;
							}
					}
					else if(bName == "select_rook")
					{
						for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
							if(!(*it).dead && (*it).isBlack == blackControlling)
							{
								if((*it).myType->name == "Rook")
								{
									if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && !(*it).selected)
										continue;
									(*it).selected = true;
								}
								else
									(*it).selected = false;
							}
					}
					else if(bName == "select_knight")
					{
						for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
							if(!(*it).dead && (*it).isBlack == blackControlling)
							{
								if((*it).myType->name == "Knight")
								{
									if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && !(*it).selected)
										continue;
									(*it).selected = true;
								}
								else
									(*it).selected = false;
							}
					}
					else if(bName == "select_bishop")
					{
						for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
							if(!(*it).dead && (*it).isBlack == blackControlling)
							{
								if((*it).myType->name == "Bishop")
								{
									if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && !(*it).selected)
										continue;
									(*it).selected = true;
								}
								else
									(*it).selected = false;
							}
					}
					else if(bName == "select_pawn")
					{
						for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
							if(!(*it).dead && (*it).isBlack == blackControlling)
							{
								if((*it).myType->name == "Pawn")
								{
									if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && !(*it).selected)
										continue;
									(*it).selected = true;
								}
								else
									(*it).selected = false;
							}
					}
				}
			}
			if(!clickedButton)
			{
				selectingWithLeftButton = true;
				selectingWithRightButton = false;
			}
		}
		else if(e.mouseButton.button == sf::Mouse::Right)
		{
			selectingWithRightButton = true;
			selectingWithLeftButton = false;
		}
		if(selectingWithLeftButton || selectingWithRightButton)
		{
			sf::Vector2i screenPosition(e.mouseButton.x,e.mouseButton.y);
			selectionBoxStart = ((sf::Vector2f)screenPosition - board->boardSprite.getPosition())/(float)board->magnificationLevel();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if((e.mouseButton.button == sf::Mouse::Left && selectingWithLeftButton) ||
			(e.mouseButton.button == sf::Mouse::Right && selectingWithRightButton))
		{
			sf::Vector2i screenPosition(e.mouseButton.x,e.mouseButton.y);
			sf::Vector2f selectionBoxEnd = ((sf::Vector2f)screenPosition - board->boardSprite.getPosition())/(float)board->magnificationLevel();
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
	realTicks++;
	moneyText.setString(std::string(blackControlling ? "Black " : "White ") +"money: " + std::to_string((long long)(blackControlling ? blackMoney : whiteMoney)));

	if(selectingWithLeftButton || selectingWithRightButton)
	{
		sf::Vector2f SelectionBoxStartScreenCoords = selectionBoxStart*(float)board->magnificationLevel()+board->boardSprite.getPosition();
		selectionBoxShape.setPosition(SelectionBoxStartScreenCoords);
		selectionBoxShape.setSize((sf::Vector2f)lastMousePosition - SelectionBoxStartScreenCoords);
	}
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

	int pieceCountBlack = 0;
	int pieceCountWhite = 0;
	for(auto it = pieces->pieces.begin(); it != pieces->pieces.end(); ++it)
	{
		Piece* p = &*it;
		if(!p->dead)
		{
			if(p->isBlack)
				pieceCountBlack++;
			else
				pieceCountWhite++;
			p->cooldown();
			if(p->energy > ENERGY_THRESHOLD)
			{
				p->energy -= ENERGY_THRESHOLD;
				pieces->AIMove(p->id,board);
			}
		}
	}
	whiteCount.setString("White pieces: " + std::to_string((long long)pieceCountWhite));
	blackCount.setString("Black pieces: " + std::to_string((long long)pieceCountBlack));

	if(ticks%5 == 0)
	{
		board->updateBoardImage();
	}
}