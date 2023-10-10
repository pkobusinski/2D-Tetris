#pragma once
#include "brick.h"
class Brick_Straight :public Brick
{
	
public: 
	Brick_Straight(Config* _cfg, sf::RenderWindow* _wnd);
	~Brick_Straight();
};

