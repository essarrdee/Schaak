#pragma once
#include "PieceType.h"
#include <vector>
class ChessSet
{
public:
	ChessSet(void);
	~ChessSet(void);
	std::vector<PieceType*> pieceTypes;
};

