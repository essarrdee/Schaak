#include "Piece.h"
#include "utilities.h"


Piece::Piece(void)
{
	energy = 0;
	myType = nullptr;
	isBlack = true;
	position = sf::Vector2i(0,0);
	dead = true;
	selected = false;
	destination = sf::IntRect(0,0,BOARD_SIZE_X,BOARD_SIZE_Y);
}


Piece::~Piece(void)
{
}

void Piece::cooldown()
{
	
	energy += isBlack ? myType->energyPerTurnBlack : myType->energyPerTurnWhite;
}
void Piece::alterCover(Board* b, int difference)
{
	for(auto it = myType->attackOffsets.begin(); it != myType->attackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = position + *it;
		if(onMap(newPosition))
		{
			if(isBlack)
				b->alterBlackCover(newPosition,difference);
			else
				b->alterWhiteCover(newPosition,difference);
		}
	}
	for(auto it = myType->moveAttackOffsets.begin(); it != myType->moveAttackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = position + *it;
		if(onMap(newPosition))
		{
			if(isBlack)
				b->alterBlackCover(newPosition,difference);
			else
				b->alterWhiteCover(newPosition,difference);
		}
	}
}

void Piece::displace(Board* b)
{
	alterCover(b,-1);
	b->occupants[position.x][position.y] = NULL_PIECE;
}

void Piece::place(Board* b, sf::Vector2i xy)
{
	position = xy;
	
	b->occupants[xy.x][xy.y] = id;
	alterCover(b,1);
}


int Piece::distanceToDestination(sf::Vector2i xy)
{
	int xdist = std::max(0, std::max(
		destination.left - xy.x,
		xy.x -destination.left - destination.width));
	int ydist = std::max(0, std::max(
		destination.top - xy.y,
		xy.y -destination.top - destination.height));
	return xdist+ydist;
}