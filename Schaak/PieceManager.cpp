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
	if(freeSlots.size() > 0)
	{
		PieceID slot = freeSlots.front();
		freeSlots.pop_front();
		pieces[slot] = *p;
		pieces[slot].id = slot;
		pieces[slot].uniqueID = nextUniqueID;
		return slot;
	}
	else
	{
		PieceID slot = pieces.size();
		pieces.push_back(*p);
		pieces[slot].id = slot;
		pieces[slot].uniqueID = nextUniqueID;
		return slot;
	}
}

void PieceManager::freeSlot(PieceID slot)
{
	freeSlots.push_back(slot);
}
