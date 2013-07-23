#include "PieceType.h"


PieceType::PieceType(void)
{
}


PieceType::~PieceType(void)
{
}

void PieceType::cooldown(Piece* p)
{
	p->energy += energyPerTurn;
}
void PieceType::alterCover(Piece* p, Board* b, int difference)
{
	// C++0x required
	for(auto it = coverOffsets.begin(); it != coverOffsets.end(); ++it)
	{
		sf::Vector2i position = p->position + *it;
		// TODO check for position out-of-bounds
		if(p->playerOwned)
			b->alterPlayerCover(position.x,position.y,difference);
		else
			b->alterEnemyCover(position.x,position.y,difference);
	}
}