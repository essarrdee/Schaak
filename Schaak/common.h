#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include "utilities.h"

static const char* GAME_NAME = "Schaak!";

static const unsigned int WINDOW_MIN_WIDTH = 1024;
static const unsigned int WINDOW_MIN_HEIGHT = 768;

static const sf::Color WHITE_SQUARE_COLOR = sf::Color::Color(64,64,64);
static const sf::Color BLACK_SQUARE_COLOR = sf::Color::Color(128,128,128);

static const int GAME_CONTINUE = 0;
static const int GAME_VICTORY = 1;
static const int GAME_DEFEAT = 2;

static const sf::Vector2u BOARD_REGIONS = sf::Vector2u(8,8);
static const sf::Vector2u REGION_SIZE = sf::Vector2u(100,75);

static const sf::Vector2u BOARD_SIZE = BOARD_REGIONS*BOARD_SIZE;