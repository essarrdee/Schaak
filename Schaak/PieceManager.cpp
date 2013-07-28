#include "PieceManager.h"
#include "utilities.h"


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
	if(nullPiece(p))
		return;
	Piece* pp = &pieces[p];
	pp->dead = true;
	pp->alterCover(b,-1);
	b->occupants[pp->position.x][pp->position.y] = NULL_PIECE;
	freeSlots.push_back(p);
}

void PieceManager::randomMove(PieceID p, Board* b)
{
	pieces[p].displace(b);
	std::vector<sf::Vector2i> movePossibilities;
	for(auto it = pieces[p].myType->moveAttackOffsets.begin(); it != pieces[p].myType->moveAttackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = pieces[p].position + *it;
		if(onMap(newPosition))
			movePossibilities.push_back(newPosition);
	}
	for(auto it = pieces[p].myType->moveOffsets.begin(); it != pieces[p].myType->moveOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = pieces[p].position + *it;
		if(onMap(newPosition))
			movePossibilities.push_back(newPosition);
	}
	sf::Vector2i chosenPosition = vectorRandomChoice(movePossibilities,pieces[p].position);
	killPiece(b->occupants[chosenPosition.x][chosenPosition.y],b);
	pieces[p].place(b,chosenPosition);
}