#include "PieceType.h"
#include "Logger.h"
#include <iostream>
#include <fstream>


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
		// TODO check for position out-of-bounds
		if(p->playerOwned)
			b->alterPlayerCover(position.x,position.y,difference);
		else
			b->alterEnemyCover(position.x,position.y,difference);
	}
	for(auto it = moveAttackOffsets.begin(); it != attackOffsets.end(); ++it)
	{
		sf::Vector2i position = p->position + *it;
		// TODO check for position out-of-bounds
		if(p->playerOwned)
			b->alterPlayerCover(position.x,position.y,difference);
		else
			b->alterEnemyCover(position.x,position.y,difference);
	}
}