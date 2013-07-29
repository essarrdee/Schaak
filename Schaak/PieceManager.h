#pragma once
#include <vector>
#include <functional>
#include <deque>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Behaviour.h"
#include <tuple>
class Piece;
class PieceManager
{
public:
	PieceManager(void);
	~PieceManager(void);
	std::vector<Piece> pieces;
	std::deque<unsigned int> freeSlots;
	PieceID addPiece(Piece* p);
	void killPiece(PieceID p,Board* b);
	void freeSlot(PieceID slot);
	sf::Sprite piecesSprite;
	void randomMove(PieceID p, Board* b);
	void AIMove(PieceID p, Board* b);
	int valuePosition(sf::Vector2i xy, PieceID p, Board* b, Behaviour* bh, bool capture);
	void drawBox(sf::Vector2f start, sf::Vector2f end, bool black, bool rightClick);
private:
	UniquePieceID nextUniqueID;
	static const int initialSlots = 4000;
	sf::Texture piecesTexture;
	std::vector<std::tuple<int,int,sf::Vector2i> > movePossibilities;
};

