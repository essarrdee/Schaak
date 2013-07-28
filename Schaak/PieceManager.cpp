#include "PieceManager.h"
#include "utilities.h"
#include "Logger.h"


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
	pieces[slot].energy = rand()%(ENERGY_THRESHOLD/2);
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

int PieceManager::valuePosition(sf::Vector2i xy, PieceID p, Board* b, Behaviour* bh, bool capture)
{
	int value = 0;
	for(auto bit = bh->values.begin(); bit != bh->values.end(); ++bit)
	{
		int valueCode = (*bit).first;
		int coefficient = (*bit).second;
		switch(valueCode)
		{
		case ENEMY_COVER:
			value += coefficient * (pieces[p].playerOwned ? 
				b->enemyCoverCount[xy.x][xy.y] :
			    b->playerCoverCount[xy.x][xy.y]);
			break;
		case FRIEND_COVER:
			value += coefficient * (pieces[p].playerOwned ? 
				b->playerCoverCount[xy.x][xy.y] :
			    b->enemyCoverCount[xy.x][xy.y]);
			break;
		case OWN_VALUE:
			value += coefficient * pieces[p].myType->value;
			break;
		case ENEMY_VALUE :
			if(capture)
				value += coefficient * pieces[b->occupants[xy.x][xy.y]].myType->value;
			break;
		}
	}
	return value;
}

void PieceManager::AIMove(PieceID p, Board* b, Behaviour* bh)
{
	pieces[p].displace(b);
	movePossibilities.clear();
	//std::vector<std::tuple<int,int,sf::Vector2i> > movePossibilities;
	for(auto it = pieces[p].myType->moveAttackOffsets.begin(); it != pieces[p].myType->moveAttackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = pieces[p].position + *it;
		if(onMap(newPosition))
		{
			PieceID pp = b->occupants[newPosition.x][newPosition.y];
			if(!nullPiece(pp))
				if(pieces[pp].playerOwned == pieces[p].playerOwned)
					continue;
			int value = valuePosition(newPosition,p,b,bh,!nullPiece(pp));
			movePossibilities.push_back(std::make_tuple(value,rand(),newPosition));
		}

	}
	for(auto it = pieces[p].myType->moveOffsets.begin(); it != pieces[p].myType->moveOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = pieces[p].position + *it;
		if(onMap(newPosition))
		{
			if(nullPiece (b->occupants[newPosition.x][newPosition.y]))
			{
				int value = valuePosition(newPosition,p,b,bh,false);

				movePossibilities.push_back(std::make_tuple(value,rand(),newPosition));
			}
		}
	}
	for(auto it = pieces[p].myType->attackOffsets.begin(); it != pieces[p].myType->attackOffsets.end(); ++it)
	{
		sf::Vector2i newPosition = pieces[p].position + *it;
		if(onMap(newPosition))
		{
			PieceID pp = b->occupants[newPosition.x][newPosition.y];
			if(!nullPiece(pp))
			{
				if(pieces[pp].playerOwned != pieces[p].playerOwned)
				{
					int value = valuePosition(newPosition,p,b,bh,true);
					movePossibilities.push_back(std::make_tuple(value,rand(),newPosition));
				}
			}
		}
	}
	std::sort(movePossibilities.begin(),movePossibilities.end(),
		[]
	(const std::tuple<int,int,sf::Vector2i>& left, const std::tuple<int,int,sf::Vector2i>& right) -> bool
	{
		if(std::get<0>(left) != std::get<0>(right))
			return std::get<0>(left) < std::get<0>(right);
		return std::get<1>(left) < std::get<1>(right);
	}
		);
	sf::Vector2i chosenPosition = pieces[p].position;
	if(movePossibilities.size() > 0)
	{
		chosenPosition = std::get<2>(movePossibilities.back());
		killPiece(b->occupants[chosenPosition.x][chosenPosition.y],b);
	}
	pieces[p].place(b,chosenPosition);
}