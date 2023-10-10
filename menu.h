#pragma once
#include "dlg_window.h"

class Menu : public Dlg_window
{
	
public:
	Menu(Config* _cfg, sf::RenderWindow *_wnd, float _width, float _height);
	void draw();
};

