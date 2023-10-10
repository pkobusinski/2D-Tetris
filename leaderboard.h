#pragma once
#include "dlg_window.h"
#include "config.h"

class Leaderboard : public Dlg_window
{

public:
	Leaderboard(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height);
	void draw();
};


