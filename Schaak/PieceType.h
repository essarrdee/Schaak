#pragma once
#include <list>
#include <string>
#include "Piece.h"
#include "Board.h"
#include "Behaviour.h"

class Piece;

class Board;

class PieceType
{
public:
	PieceType(std::string filename);
	~PieceType(void);
	sf::IntRect spriteLocation(int magnificationCode, bool black);

	// TODO make these public gets or constants initialised by the constructor
	int energyPerTurnBase;
	int energyPerTurnWhite;
	int energyPerTurnBlack;
	std::list<sf::Vector2i> moveOffsets;
	std::list<sf::Vector2i> attackOffsets;
	std::list<sf::Vector2i> moveAttackOffsets;
	int spritePosition;
	std::string name;
	int value;
	Behaviour* behaviourBlack;
	Behaviour* behaviourWhite;
	int blockBlack;
	int blockWhite;

private:
};

