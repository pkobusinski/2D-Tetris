#include "brick_Jay.h"

Brick_Jay::Brick_Jay(Config* _cfg, sf::RenderWindow* _wnd): Brick(_cfg, _wnd)
{
	size = 3;
	type = BrickType::JAY;
	status = BrickStatus::FALLING;
	shape[0][0] = 1;
	shape[1][0] = 1;
	shape[1][1] = 1;
	shape[1][2] = 1;

}
