#include "brick_Square.h"

Brick_Square::Brick_Square(Config* _cfg, sf::RenderWindow* _wnd) :Brick(_cfg, _wnd)
{
	size = 2;
	type = BrickType::SQUARE;
	status = BrickStatus:: FALLING;
	shape[0][0] = 1;
	shape[0][1] = 1;
	shape[1][0] = 1;
	shape[1][1] = 1;
}

Brick_Square::~Brick_Square()
{
}
