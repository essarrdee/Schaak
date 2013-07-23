#pragma once
#include <list>
#include "Piece.h"
#include "Board.h"

class PieceType
{
public:
	PieceType(void);
	~PieceType(void);
	void cooldown(Piece* p);
	void alterCover(Piece* p, Board* b, int difference);
private:
	int energyPerTurn;
	std::list<sf::Vector2i> coverOffsets;
};

