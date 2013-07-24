#include "PieceType.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include "utilities.h"

PieceType::PieceType(std::string filename)
{
	std::ifstream f(CHESS_SET_PATH + filename);
	f >> name;
	LINFO("Piece name: "); LAPPEND(name);
	f >> energyPerTurn;
	LINFO("Energy per turn: "); LAPPEND(energyPerTurn);
	std::string offsetType;
	sf::Vector2i offset;
	int offsetCount = 0;
	while(f.good())
	{
		offsetCount++;
		f >> offsetType >> offset.x >> offset.y;
		if(offsetType == "ma")
			moveAttackOffsets.push_back(offset);
		else if(offsetType == "m")
			moveOffsets.push_back(offset);
		else if(offsetType == "a")
			attackOffsets.push_back(offset);
	}
	LINFO("Offset count: "); LAPPEND(offsetCount);
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
	for(auto it = attackOffsets.begin(); it != attackOffsets.end(); ++it)
	{
		sf::Vector2i position = p->position + *it;
		if(onMap(position))
		{
			if(p->playerOwned)
				b->alterPlayerCover(position.x,position.y,difference);
			else
				b->alterEnemyCover(position.x,position.y,difference);
		}
	}
	for(auto it = moveAttackOffsets.begin(); it != moveAttackOffsets.end(); ++it)
	{
		sf::Vector2i position = p->position + *it;
		if(onMap(position))
		{
			if(p->playerOwned)
				b->alterPlayerCover(position.x,position.y,difference);
			else
				b->alterEnemyCover(position.x,position.y,difference);
		}
	}
}

void PieceType::randomMove(Piece* p, Board* b)
{
	alterCover(p,b,-1);
	std::vector<sf::Vector2i> movePossibilities;
	for(auto it = moveAttackOffsets.begin(); it != moveAttackOffsets.end(); ++it)
	{
		sf::Vector2i position = p->position + *it;
		if(onMap(position))
			movePossibilities.push_back(position);
	}
	for(auto it = moveOffsets.begin(); it != moveOffsets.end(); ++it)
	{
		sf::Vector2i position = p->position + *it;
		if(onMap(position))
			movePossibilities.push_back(position);
	}
	p->position = vectorRandomChoice(movePossibilities,p->position);
	alterCover(p,b,1);
}