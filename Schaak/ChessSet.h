#pragma once
#include "PieceType.h"
#include "BehaviourManager.h"
#include <vector>
class ChessSet
{
public:
	ChessSet(BehaviourManager* bm);
	~ChessSet(void);
	std::vector<PieceType*> pieceTypes;
};

