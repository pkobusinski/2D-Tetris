#include "brick_Tee.h"

Brick_Tee::Brick_Tee(Config* _cfg, sf::RenderWindow* _wnd) : Brick(_cfg, _wnd)
{
	size = 3;
	type = BrickType::TEE;
	status = BrickStatus::FALLING;
	shape[1][0] = 1;
	shape[0][1] = 1;
	shape[1][1] = 1;
	shape[1][2] = 1;

}

Brick_Tee::~Brick_Tee()
{
}
