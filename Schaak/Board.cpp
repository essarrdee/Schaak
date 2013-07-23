#include "Board.h"


Board::Board(void)
{
	for(MapIterator it((sf::Vector2i)BOARD_SIZE);it.good(); ++it)
	{
		int x = (*it).x;
		int y = (*it).y;
		playerCoverCount[x][y] = 0;
		enemyCoverCount[x][y] = 0;
		updateCoverDifference(x,y);

	}
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

void Board::alterPlayerCover(unsigned int x, unsigned int y, int difference)
{
	playerCoverCount[x][y] += difference;
	updateCoverDifference(x,y);
}
void Board::alterEnemyCover(unsigned int x, unsigned int y, int difference)
{
	enemyCoverCount[x][y] += difference;
	updateCoverDifference(x,y);
}

void Board::updateCoverDifference(unsigned int x, unsigned int y)
{
	coverDifference[x][y] = playerCoverCount[x][y] - enemyCoverCount[x][y];
	updateBoardColour(x,y);
}

void Board::updateBoardColour(unsigned int x, unsigned int y)
{
	// TODO colour according to cover.
	// How to do this in a colourblind-friendly way?
	// Green+magenta are reasonably distinct, but combine to white
	bool squareParity = (x+y)%2 == 1;
	if(squareParity)
	{
		boardColours[4 * (BOARD_SIZE_X*y + x)] = WHITE_SQUARE_COLOR.r;
		boardColours[4 * (BOARD_SIZE_X*y + x) + 1] = WHITE_SQUARE_COLOR.g;
		boardColours[4 * (BOARD_SIZE_X*y + x) + 2] = WHITE_SQUARE_COLOR.b;
		boardColours[4 * (BOARD_SIZE_X*y + x) + 3] = WHITE_SQUARE_COLOR.a;
	}
	else
	{
		boardColours[4 * (BOARD_SIZE_X*y + x)] = BLACK_SQUARE_COLOR.r;
		boardColours[4 * (BOARD_SIZE_X*y + x) + 1] = BLACK_SQUARE_COLOR.g;
		boardColours[4 * (BOARD_SIZE_X*y + x) + 2] = BLACK_SQUARE_COLOR.b;
		boardColours[4 * (BOARD_SIZE_X*y + x) + 3] = BLACK_SQUARE_COLOR.a;
	}
	if(playerCoverCount[x][y] && !enemyCoverCount[x][y])
	{
		boardColours[4 * (BOARD_SIZE_X*y + x) + 1] = ((int)boardColours[4 * (BOARD_SIZE_X*y + x) + 1] + 255)/2;
	}
	else if(!playerCoverCount[x][y] && enemyCoverCount[x][y])
	{
		boardColours[4 * (BOARD_SIZE_X*y + x)] = ((int)boardColours[4 * (BOARD_SIZE_X*y + x) + 1] + 255)/2;
	}
}

void Board::updateBoardImage()
{
	//boardSprite.setPosition(5.f,5.f);
	boardSprite.setScale(2.f,2.f);
	boardImage.create(BOARD_SIZE_X,BOARD_SIZE_Y,boardColours);
	boardTexture.loadFromImage(boardImage);
}