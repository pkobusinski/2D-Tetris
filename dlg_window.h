                  #pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "general.h"
#include "config.h"

struct Line {
	
	std::string label;
	bool value;
	sf::Text field_1;
	sf::Text field_2;
	sf::RectangleShape checkbox;
};

class Dlg_window
{
	float width;
	float height;

protected:
	sf::RenderWindow* wnd;
	
	sf::RectangleShape frame;
	sf::Text header;
	sf::Text footer;
	sf::Sprite background;
	
	Config* cfg;
	Line lines[MAX_LINES];

	int selected_line;
	int max_lines;
	bool visible;


public: 
	Dlg_window(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height);
	~Dlg_window();

	void show();
	void hide();
	bool is_visible();

	void draw();
	void set_header(std::string _title, int _font_size = 80);
	void set_footer(std::string _title, int _font_size = 20);

	void prev_option();
	void next_option();
	int get_selected();
};

