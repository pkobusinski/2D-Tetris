#pragma once

constexpr unsigned int CELL_SIZE = 30;
constexpr unsigned int ROWS = 20;
constexpr unsigned int COLUMNS = 10;
constexpr unsigned int MAX_LINES = 5;
constexpr unsigned int LEVEL_UNIT = 200;
constexpr unsigned int GAME_SPEED = 750;
constexpr unsigned int LEADERBOARD_MAX_ITEM = 5;
constexpr unsigned int MAX_BRICK_SIZE = 4;
constexpr unsigned int MAX_BRICK_COLORS = 8;

enum class Colors { TRANS = 0, BACKGROUND = 1, TEXT = 2, TEXT_ACTIVE = 3, ITEM = 4, ITEM_ACTIVE = 5, OVERLAY_BACKGROUND = 6, BOARD = 7, GHOST = 8, BRICK = 9 };

const sf::Color palette[] = {


	sf::Color(255, 255, 255, 0),	// Transparent color
	sf::Color(0  , 0  , 0  , 150),	// Background color
	sf::Color(0  , 100, 179),		// Text color
	sf::Color(51 , 165, 255),		// Active text color
	sf::Color(0  , 100, 179),		// Item color
	sf::Color(51 , 165, 255),		// Active Item color
	sf::Color(50 , 50 , 50 , 150),	// Overlay background color
	sf::Color(10 , 10 , 10 , 150),	// Board color
	sf::Color(73 , 73 , 85),		// Ghost brick color

	//brick colors
	sf::Color(100, 10 , 85),		// Pink
	sf::Color(0  , 219, 255),		// Light blue
	sf::Color(0  , 36 , 255),		// Blue
	sf::Color(255, 146, 0),			// Orange
	sf::Color(255, 219, 0),			// Yellow
	sf::Color(0  , 219, 0),			// Light green
	sf::Color(146, 0  , 255),		// Violet
	sf::Color(219, 0  , 0),			// Red
};

