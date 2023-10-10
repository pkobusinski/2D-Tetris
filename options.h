#pragma once
#include "dlg_window.h"
#include "config.h"

class Options : public Dlg_window
{

public:
	Options(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height);
	~Options();
	void draw();
};

