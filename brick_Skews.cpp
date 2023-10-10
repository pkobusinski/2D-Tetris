#include "brick_Skews.h"

Brick_Skews::Brick_Skews(Config* _cfg, sf::RenderWindow* _wnd) : Brick(_cfg, _wnd)
{
	size = 3;
	type = BrickType::SKEWS;
	status = BrickStatus::FALLING;
	shape[0][0] = 1;
	shape[1][0] = 1;
	shape[1][1] = 1;
	shape[2][1] = 1;
}

Brick_Skews::~Brick_Skews()
{
}
