#pragma once
#include <vector>
#include <deque>
#include "Piece.h"
class PieceManager
{
public:
	PieceManager(void);
	~PieceManager(void);
	std::vector<Piece> pieces;
	std::deque<unsigned int> freeSlots;
	PieceID addPiece(Piece* p);
	void freeSlot(PieceID slot);
private:
	UniquePieceID nextUniqueID;
	static const int initialSlots = 4000;
};

