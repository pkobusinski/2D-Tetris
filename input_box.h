#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include "general.h"

class Input_box
{
	sf::RenderWindow* input_box_wnd;
	sf::RectangleShape frame;
	sf::Text label;
	sf::Text input_txt;
	sf::RectangleShape input_field;

	std::string text = "";

public:
	Input_box(Config* _cfg);
	~Input_box();
	void draw();
	std::string get_text();
};

