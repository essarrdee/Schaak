#include "Piece.h"


Piece::Piece(void)
{
	energy = 0;
	myType = nullptr;
	playerOwned = true;
	position = sf::Vector2i(0,0);
}


Piece::~Piece(void)
{
}
