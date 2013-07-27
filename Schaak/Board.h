#pragma once
#include <SFML/Graphics.hpp>
#include "common.h"
#include "Piece.h"

// Contain, maintain, and draw board data.
class Board : public sf::Drawable
{
public:
	Board(void);
	~Board(void);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void alterPlayerCover(sf::Vector2i xy, int difference); // add or subtract to a square's player cover count
	void alterEnemyCover(sf::Vector2i xy, int difference); // add or subtract to a square's enemy cover count
	void movePiece(unsigned int );
	void updateBoardImage(); // call this before rendering board
	void zoom(sf::Event::MouseWheelEvent e);
	int magnificationCode; // TODO make this a public get
	static const int magnificationLevelCount;
	static const int magnificationLevels[9];
	int magnificationLevel();
	sf::FloatRect visibleArea();
	sf::Sprite boardSprite; // TODO make just a function to get board position public
	void scroll(sf::Vector2f offset);
private:
	unsigned int playerCoverCount[BOARD_SIZE_X][BOARD_SIZE_Y];
	unsigned int enemyCoverCount[BOARD_SIZE_X][BOARD_SIZE_Y];
	unsigned int coverDifference[BOARD_SIZE_X][BOARD_SIZE_Y];
	PieceID occupants[BOARD_SIZE_X][BOARD_SIZE_Y];
	void updateCoverDifference(sf::Vector2i xy);  // call this after altering player or enemy cover counts
	sf::Uint8 boardColours[4*BOARD_SIZE_X*BOARD_SIZE_Y]; // RGBA pixels describing board image
	void updateBoardColour(sf::Vector2i xy); // call this after altering player or enemy cover counts
	void boundPosition();

	sf::Image boardImage;
	sf::Texture boardTexture;
};


