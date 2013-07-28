#include "Piece.h"
#include "utilities.h"


Piece::Piece(void)
{
	energy = 0;
	myType = nullptr;
	playerOwned = true;
	position = sf::Vector2i(0,0);
	dead = true;
}


Piece::~Piece(void)
{
}

void Piece::cooldown()
{
	energy += myType->energyPerTurn;
}
void Piece::alterCover(Board* b, int difference)
{
	for(auto it = myType->attackOffsets.begin(); it != myType->attackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = position + *it;
		if(onMap(newPosition))
		{
			if(playerOwned)
				b->alterPlayerCover(newPosition,difference);
			else
				b->alterEnemyCover(newPosition,difference);
		}
	}
	for(auto it = myType->moveAttackOffsets.begin(); it != myType->moveAttackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = position + *it;
		if(onMap(newPosition))
		{
			if(playerOwned)
				b->alterPlayerCover(newPosition,difference);
			else
				b->alterEnemyCover(newPosition,difference);
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
