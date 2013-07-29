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
			value += coefficient * (pieces[p].isBlack ? 
				b->enemyCoverCount[xy.x][xy.y] :
			    b->playerCoverCount[xy.x][xy.y]);
			break;
		case FRIEND_COVER:
			value += coefficient * (pieces[p].isBlack ? 
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
		case DESTINATION_DISTANCE:
			value += coefficient * pieces[p].distanceToDestination(xy);
			break;
		}
	}
	return value;
}

void PieceManager::AIMove(PieceID p, Board* b)
{
	Behaviour* bh = pieces[p].isBlack ? pieces[p].myType->behaviourBlack : pieces[p].myType->behaviourWhite;
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
				if(pieces[pp].isBlack == pieces[p].isBlack)
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
				if(pieces[pp].isBlack != pieces[p].isBlack)
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


void PieceManager::drawBox(sf::Vector2f start, sf::Vector2f end, bool black, bool rightClick)
{
	sf::Vector2i startSquare, endSquare;
	startSquare.x = (int)std::min(start.x,end.x);
	startSquare.y = (int)std::min(start.y,end.y);
	endSquare.x = (int)std::max(start.x,end.x)+1;
	endSquare.y = (int)std::max(start.y,end.y)+1;
	sf::Vector2i size = endSquare - startSquare;
	sf::IntRect drawnRect(startSquare,size);
	if(rightClick)
	{

		for(auto it = pieces.begin(); it != pieces.end(); ++it)
			{
				if((*it).selected && !(*it).dead && black == (*it).isBlack)
					(*it).destination = drawnRect;
			}
	}
	else
		for(auto it = pieces.begin(); it != pieces.end(); ++it)
		{
			(*it).selected = (!(*it).dead && black == (*it).isBlack && drawnRect.contains((*it).position));
		}
}