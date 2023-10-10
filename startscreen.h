#pragma once
#include "dlg_window.h"
#include <SFML/Graphics.hpp>	
class Start_screen : public Dlg_window
{

public:
	Start_screen(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height);
	void draw();
};

