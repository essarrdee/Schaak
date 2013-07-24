#pragma once
#include <list>
#include <string>
#include "Piece.h"
#include "Board.h"

class Piece;

class PieceType
{
public:
	PieceType(std::string filename);
	~PieceType(void);
	void cooldown(Piece* p);
	void alterCover(Piece* p, Board* b, int difference);
	void randomMove(Piece* p, Board* b);
private:
	int energyPerTurn;
	std::list<sf::Vector2i> moveOffsets;
	std::list<sf::Vector2i> attackOffsets;
	std::list<sf::Vector2i> moveAttackOffsets;
	std::string name;
};

