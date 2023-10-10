#pragma once
#include "brick.h"

class Brick_Square: public Brick
{

public:
	Brick_Square(Config* _cfg, sf::RenderWindow *_wnd);
	~Brick_Square();
};

