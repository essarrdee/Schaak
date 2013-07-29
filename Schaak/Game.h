#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "ChessSet.h"
#include "PieceType.h"
#include "Piece.h"
#include "PieceManager.h"
#include "BehaviourManager.h"

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
	BehaviourManager* behaviours;
	long int ticks;
	long int realTicks;
	bool paused;
	bool pauseStateChanged;
	sf::Vector2i lastMousePosition;
	bool mouseInWindow;
	bool blackControlling;
	sf::Vector2f selectionBoxStart;
	sf::RectangleShape selectionBoxShape;
	bool selectingWithLeftButton;
	bool selectingWithRightButton;
	void Game::switchControl();
	sf::Text blackCount;
	sf::Text whiteCount;
	sf::Text moneyText;
	sf::Font defaultFont;
	sf::Texture interfaceTexture;
	sf::Sprite interfaceSprite;
	int whiteMoney;
	int blackMoney;
	std::vector<sf::IntRect> buttonLocations;
	std::vector<sf::RectangleShape> buttons;
	std::vector<std::string> buttonNames;
};