#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "ChessSet.h"
#include "PieceType.h"
#include "Piece.h"
#include "PieceManager.h"

class Game : public sf::Drawable
{
public:
	Game(void);
	~Game(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawPieces(sf::RenderTarget& target, sf::RenderStates states) const;
	void processEvent(sf::Event e);
	int gameState();
	void simulate();
private:
	Board* board;
	ChessSet* chessSet;
	PieceManager* pieces;
	long int ticks;
	bool paused;
};
