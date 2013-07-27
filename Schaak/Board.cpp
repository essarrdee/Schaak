#include "Board.h"
#include "utilities.h"
#include "Interface.h"

const int Board::magnificationLevelCount = 9;
const int Board::magnificationLevels[9] = {2,3,4,6,8,12,16,24,32};

Board::Board(void)
{
	for(MapIterator it((sf::Vector2i)BOARD_SIZE);it.good(); ++it)
	{
		int x = (*it).x;
		int y = (*it).y;
		playerCoverCount[x][y] = 0;
		enemyCoverCount[x][y] = 0;
		occupants[x][y] = NULL_PIECE;
		updateCoverDifference(*it);

	}
	magnificationCode = 0;
	updateBoardImage();
	boardSprite.setTexture(boardTexture);
}


Board::~Board(void)
{
}


void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(boardSprite);
}

void Board::alterPlayerCover(sf::Vector2i xy, int difference)
{
	playerCoverCount[xy.x][xy.y] += difference;
	updateCoverDifference(xy);
}
void Board::alterEnemyCover(sf::Vector2i xy, int difference)
{
	enemyCoverCount[xy.x][xy.y] += difference;
	updateCoverDifference(xy);
}

void Board::updateCoverDifference(sf::Vector2i xy)
{
	coverDifference[xy.x][xy.y] = playerCoverCount[xy.x][xy.y] - enemyCoverCount[xy.x][xy.y];
	updateBoardColour(xy);
}

void Board::updateBoardColour(sf::Vector2i xy)
{
	// TODO colour according to cover.
	// How to do this in a colourblind-friendly way?
	// Green+magenta are reasonably distinct, but combine to white
	bool squareParity = (xy.x+xy.y)%2 == 1;
	if(squareParity)
	{
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x)] = WHITE_SQUARE_COLOR.r;
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 1] = WHITE_SQUARE_COLOR.g;
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 2] = WHITE_SQUARE_COLOR.b;
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 3] = WHITE_SQUARE_COLOR.a;
	}
	else
	{
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x)] = BLACK_SQUARE_COLOR.r;
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 1] = BLACK_SQUARE_COLOR.g;
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 2] = BLACK_SQUARE_COLOR.b;
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 3] = BLACK_SQUARE_COLOR.a;
	}
	if(playerCoverCount[xy.x][xy.y] && !enemyCoverCount[xy.x][xy.y])
	{
		boardColours[4 *(BOARD_SIZE_X*xy.y + xy.x) + 1] = ((int)boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 1] + 255)/2;
	}
	else if(!playerCoverCount[xy.x][xy.y] && enemyCoverCount[xy.x][xy.y])
	{
		boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x)] = ((int)boardColours[4 * (BOARD_SIZE_X*xy.y + xy.x) + 1] + 255)/2;
	}
}

void Board::updateBoardImage()
{
	//boardSprite.setPosition(5.f,5.f);
	boardSprite.setScale((float)magnificationLevel(),(float)magnificationLevel());
	boardImage.create(BOARD_SIZE_X,BOARD_SIZE_Y,boardColours);
	boardTexture.loadFromImage(boardImage);
}

void Board::zoom(sf::Event::MouseWheelEvent e)
{
	sf::Vector2f mouseWindowPosition((float)e.x,(float)e.y);
	int newMagnificationCode = magnificationCode + e.delta;
	newMagnificationCode = bound(newMagnificationCode,0,magnificationLevelCount-1);
	sf::Vector2f boardTopLeft = boardSprite.getPosition();
	float magnificationRatio = magnificationLevels[newMagnificationCode]/(float)magnificationLevels[magnificationCode];
	sf::Vector2f newBoardTopLeft = mouseWindowPosition - (mouseWindowPosition - boardTopLeft)*magnificationRatio;
	boardSprite.setPosition(newBoardTopLeft);
	magnificationCode = newMagnificationCode;
	boardSprite.setScale((float)magnificationLevel(),(float)magnificationLevel());
	boundPosition();
}


sf::FloatRect Board::visibleArea()
{
	sf::Vector2f topLeft = -boardSprite.getPosition()/sf::Vector2f(magnificationLevel(),magnificationLevel());
	sf::Vector2f size = (sf::Vector2f)Interface::windowSize/sf::Vector2f(magnificationLevel(),magnificationLevel());
	return sf::FloatRect(topLeft,size);
}

int Board::magnificationLevel()
{
	return magnificationLevels[magnificationCode];
}

void Board::boundPosition()
{
	sf::FloatRect bounds = boardSprite.getGlobalBounds();
	sf::Vector2f newPosition = boardSprite.getPosition();
	if(bounds.left > 0.0)
	{
		newPosition.x = 0.0;
	}
	else if(bounds.left+bounds.width < VIEWPORT.left+VIEWPORT.width)
	{
		newPosition.x = VIEWPORT.left + VIEWPORT.width - bounds.width;
	}
	
	if(bounds.top > 0.0)
	{
		newPosition.y = 0.0;
	}
	else if(bounds.top+bounds.height < VIEWPORT.top+VIEWPORT.height)
	{
		newPosition.y = VIEWPORT.top + VIEWPORT.height - bounds.height;
	}
	boardSprite.setPosition(newPosition);
}

