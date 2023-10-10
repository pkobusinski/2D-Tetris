#include "brick_Skewz.h"

Brick_Skewz::Brick_Skewz(Config* _cfg, sf::RenderWindow* _wnd):Brick(_cfg, _wnd)
{
	size = 3;
	type = BrickType::SKEWZ;
	status = BrickStatus::FALLING;
	shape[0][1] = 1;
	shape[1][1] = 1;
	shape[1][0] = 1;
	shape[2][0] = 1;
}

Brick_Skewz::~Brick_Skewz()
{
}
