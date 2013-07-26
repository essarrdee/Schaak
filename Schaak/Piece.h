#pragma once
#include <SFML/System/Vector2.hpp>
#include "PieceType.h"
#include "common.h"

class PieceType;


static inline bool nullPiece(PieceID ID)
{
	return ID < 0;
}
static const int NULL_PIECE = -1;

class Piece
{
public:
	Piece(void);
	~Piece(void);
	int energy;
	PieceType* myType;
	bool playerOwned;
	sf::Vector2i position;
	UniquePieceID uniqueID;
	PieceID id;
	bool dead;
};

