#pragma once
#include <SFML/System/Vector2.hpp>
#include "PieceType.h"

class PieceType;

typedef long int UniquePieceID;
typedef unsigned int PieceID;

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

