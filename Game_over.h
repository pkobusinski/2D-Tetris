#pragma once
#include "dlg_window.h"
class Game_over : public Dlg_window
{

public:
	Game_over(sf::RenderWindow* _wnd, float _width, float _height);
	void draw();
};

