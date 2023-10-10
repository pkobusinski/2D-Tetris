#pragma once
#include <SFML/Graphics.hpp>
#include "general.h"
#include "brick.h"
#include <iostream>

class Board {

	sf::RenderWindow* wnd;

public:
	char board_matrix[ROWS + 1][COLUMNS + 1];

	Board(sf::RenderWindow* _wnd);
	~Board();
	
	void init();
	void draw();
	
	void set_busy(Brick* _brick);
	bool is_row_full(int _row);
	char* get_row();
	void clear_row(int _row);
	
};