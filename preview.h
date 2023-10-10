#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "brick.h"
#include "config.h"

class Preview
{
	sf::RenderWindow* wnd;

	sf::RectangleShape prev_wnd;
	sf::Text prev_txt;
	sf::Font MyFont;
public:
	Preview(Config* _cfg, sf::RenderWindow* _wnd);
	~Preview();
	void draw(Brick* next_brick);
};

