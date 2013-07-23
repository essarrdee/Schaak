#pragma once
#include <SFML/Graphics.hpp>
#include "common.h"

// Contain, maintain, and draw board data.
class Board : public sf::Drawable
{
public:
	Board(void);
	~Board(void);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void alterPlayerCover(unsigned int x, unsigned int y, int difference); // add or subtract to a square's player cover count
	void alterEnemyCover(unsigned int x, unsigned int y, int difference); // add or subtract to a square's enemy cover count
private:
	unsigned int playerCoverCount[BOARD_SIZE_X][BOARD_SIZE_Y];
	unsigned int enemyCoverCount[BOARD_SIZE_X][BOARD_SIZE_Y];
	unsigned int coverDifference[BOARD_SIZE_X][BOARD_SIZE_Y];
	void updateCoverDifference(unsigned int x, unsigned int y);  // call this after altering player or enemy cover counts
	sf::Uint8 boardColours[4*BOARD_SIZE_X*BOARD_SIZE_Y]; // RGBA pixels describing board image
	void updateBoardColour(unsigned int x, unsigned int y); // call this after altering player or enemy cover counts
	void updateBoardImage(); // call this before rendering board

	sf::Image boardImage;
	sf::Texture boardTexture;
	sf::Sprite boardSprite;
};

