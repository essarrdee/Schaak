#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
//#include "utilities.h"

static const std::string GAME_NAME = "Schaak!";

static const unsigned int WINDOW_MIN_WIDTH = 1024;
static const unsigned int WINDOW_MIN_HEIGHT = 768;

static const sf::Color WHITE_SQUARE_COLOR = sf::Color::Color(64,64,64);
static const sf::Color BLACK_SQUARE_COLOR = sf::Color::Color(128,128,128);

static const int GAME_CONTINUE = 0;
static const int GAME_VICTORY = 1;
static const int GAME_DEFEAT = 2;

static const unsigned int BOARD_REGIONS_X = 8;
static const unsigned int BOARD_REGIONS_Y = 8;
static const sf::Vector2u BOARD_REGIONS = sf::Vector2u(BOARD_REGIONS_X,BOARD_REGIONS_Y);
static const unsigned int REGION_SIZE_X = 50; // 800x600 map is very expensive to update every tick; use 400x280 instead.
static const unsigned int REGION_SIZE_Y = 35; // may be possible to do 800x600 if map regions are given separate images, updated only when necessary.
static const sf::Vector2u REGION_SIZE = sf::Vector2u(REGION_SIZE_X,REGION_SIZE_Y);

static const unsigned int BOARD_SIZE_X = BOARD_REGIONS_X*REGION_SIZE_X; 
static const unsigned int BOARD_SIZE_Y = BOARD_REGIONS_Y*REGION_SIZE_Y;
static const sf::Vector2u BOARD_SIZE = sf::Vector2u(BOARD_SIZE_X,BOARD_SIZE_Y);
static const sf::Vector2u VIEWPORT_SIZE = sf::Vector2u(2*BOARD_SIZE_X,2*BOARD_SIZE_Y);
static const sf::IntRect VIEWPORT = sf::IntRect(0,0,2*BOARD_SIZE_X,2*BOARD_SIZE_Y);

static const std::string RESOURCE_PATH = "Resources/";
static const std::string IMAGE_PATH = RESOURCE_PATH + "Images/";
static const std::string CHESS_SET_PATH = RESOURCE_PATH + "Pieces/";
static const std::string PIECE_SPRITE_PATH = IMAGE_PATH + "piece_sprites.png";

static const int ENERGY_THRESHOLD = 500;


typedef long int UniquePieceID;
typedef int PieceID;

static const int BLACK_OFFSETS[9] = {0,
	                                 4,
									 4+6,
									 4+6+8,
									 4+6+8+12,
								     4+6+8+12+16,
									 4+6+8+12+16+24,
									 4+6+8+12+16+24+32,
									 4+6+8+12+16+24+32+48};
static const int WHITE_OFFSETS[9] = {0 + 2,
	                                 4 + 3,
									 4+6 + 4,
									 4+6+8 + 6,
									 4+6+8+12 + 8,
									 4+6+8+12+16 + 12,
									 4+6+8+12+16+24 + 16,
									 4+6+8+12+16+24+32 + 24,
									 4+6+8+12+16+24+32+48 + 32};