#pragma once
#include <SFML/System/Vector2.hpp>
class Piece
{
public:
	Piece(void);
	~Piece(void);
	int energy;
	int myType;
	bool playerOwned;
	sf::Vector2i position;
};

