#pragma once
#include <SFML/System/Vector2.hpp>
#include "PieceType.h"
#include "Board.h"
#include "common.h"
#include "Behaviour.h"

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
	
	void cooldown();
	void alterCover(Board* b, int difference);
	void displace(Board* b);
	void place(Board* b, sf::Vector2i xy);
	int distanceToDestination(sf::Vector2i xy);

	int energy;
	PieceType* myType;
	bool isBlack;
	sf::Vector2i position;
	UniquePieceID uniqueID;
	PieceID id;
	bool dead;
	Behaviour* behaviour;
	bool selected;
	sf::IntRect destination;
};

