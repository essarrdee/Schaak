#include "ChessSet.h"
#include "common.h"
#include "Logger.h"

#include <iostream>
#include <fstream>

ChessSet::ChessSet(void)
{
	LINFO("Loading chess set");
	std::ifstream f(CHESS_SET_PATH+"pieces");
	std::string piece_filename;
	while(f.good())
	{
		f >> piece_filename;
		LINFO("Loading piece: ");
		LAPPEND(piece_filename);
		PieceType* newPiece = new PieceType(piece_filename);
		pieceTypes.push_back(newPiece);
	}
}


ChessSet::~ChessSet(void)
{
}
