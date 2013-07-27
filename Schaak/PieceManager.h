#pragma once
#include <vector>
#include <deque>
#include <SFML/Graphics.hpp>
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
	sf::Sprite piecesSprite;
private:
	UniquePieceID nextUniqueID;
	static const int initialSlots = 4000;
	sf::Texture piecesTexture;
};

