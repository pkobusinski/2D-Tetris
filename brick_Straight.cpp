#include "brick_Straight.h"

Brick_Straight::Brick_Straight(Config* _cfg, sf::RenderWindow* _wnd):Brick(_cfg, _wnd)
{
	size = 4;
	type = BrickType:: STRAIGHT;
	status = BrickStatus::FALLING;
	shape[1][0] = 1;
	shape[1][1] = 1;
	shape[1][2] = 1;
	shape[1][3] = 1;
}

Brick_Straight::~Brick_Straight()
{
}
