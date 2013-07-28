#include "PieceManager.h"


PieceManager::PieceManager(void)
{
	nextUniqueID = 0;
	pieces.resize(initialSlots);
	for(int i=0; i<initialSlots; i++)
	{
		freeSlots.push_back(i);
	}
	piecesTexture.loadFromFile(PIECE_SPRITE_PATH);
	piecesSprite.setTexture(piecesTexture);
}


PieceManager::~PieceManager(void)
{
}

PieceID PieceManager::addPiece(Piece* p)
{
	PieceID slot;
	if(freeSlots.size() > 0)
	{
		slot = freeSlots.front();
		freeSlots.pop_front();
		pieces[slot] = *p;
	}
	else
	{
		slot = pieces.size();
		pieces.push_back(*p);
	}
	pieces[slot].id = slot;
	pieces[slot].uniqueID = nextUniqueID;
	pieces[slot].energy = rand()%pieces[slot].myType->energyPerTurn;
	nextUniqueID++;
	return slot;
}

void PieceManager::freeSlot(PieceID slot)
{
	freeSlots.push_back(slot);
}

void PieceManager::killPiece(PieceID p,Board* b)
{
	Piece* pp = &pieces[p];
	pp->alterCover(b,-1);
	b->occupants[pp->position.x][pp->position.y] = NULL_PIECE;
	freeSlots.push_back(p);
}