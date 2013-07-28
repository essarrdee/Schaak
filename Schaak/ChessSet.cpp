#include "ChessSet.h"
#include "common.h"
#include "Logger.h"

#include <iostream>
#include <fstream>

ChessSet::ChessSet(BehaviourManager* bm)
{
	LINFO("Loading chess set");
	std::ifstream f(CHESS_SET_PIECES_PATH);
	std::string piece_filename;
	while(f.good())
	{
		f >> piece_filename;
		LINFO("Loading piece: ");
		LAPPEND(piece_filename);
		PieceType* newPiece = new PieceType(piece_filename);
		newPiece->behaviourBlack = bm->behaviours[0];
		newPiece->behaviourWhite = bm->behaviours[1];
		pieceTypes.push_back(newPiece);
	}
}


ChessSet::~ChessSet(void)
{
}
