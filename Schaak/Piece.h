#pragma once
#include <SFML/System/Vector2.hpp>
#include "PieceType.h"

class PieceType;

class Piece
{
public:
	Piece(void);
	~Piece(void);
	int energy;
	PieceType* myType;
	bool playerOwned;
	sf::Vector2i position;
};

