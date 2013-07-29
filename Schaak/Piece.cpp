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
	energy += myType->energyPerTurn;
}
void Piece::alterCover(Board* b, int difference)
{
	for(auto it = myType->attackOffsets.begin(); it != myType->attackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = position + *it;
		if(onMap(newPosition))
		{
			if(isBlack)
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
			if(isBlack)
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


int Piece::distanceToDestination(sf::Vector2i xy)
{
	if(destination.contains(xy))
		return 0;
	return std::min( // Hack!
		std::min(
		abs(xy.x - destination.left),
		abs(xy.x - destination.left - destination.width)
		),
		std::min(
		abs(xy.y - destination.top),
		abs(xy.y - destination.top - destination.height)
		)
		);
}