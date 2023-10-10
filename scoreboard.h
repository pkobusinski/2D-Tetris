#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System/String.hpp>
#include <iostream>
#include "general.h"
#include "config.h"


class Scoreboard
{
	sf::RenderWindow* wnd;
	sf::Text score_txt;
	sf::Text score_value;
	sf::RectangleShape score_wnd;

public:
	Scoreboard(Config* _cfg, sf::RenderWindow* _wnd);
	~Scoreboard();

	void draw(int _points);
};

