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
	f >> spritePosition;
	LINFO("Sprite position: "); LAPPEND(spritePosition);
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



sf::IntRect PieceType::spriteLocation(int magnificationCode, bool black)
{
	int magnificationLevel = Board::magnificationLevels[magnificationCode];
	sf::Vector2i size(magnificationLevel,magnificationLevel);
	sf::Vector2i offset(magnificationLevel*spritePosition,black ? BLACK_OFFSETS[magnificationCode] : WHITE_OFFSETS[magnificationCode]);
	return sf::IntRect(offset,size);
}