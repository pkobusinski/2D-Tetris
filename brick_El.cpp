#include "brick_El.h"

Brick_El::Brick_El(Config* _cfg, sf::RenderWindow* _wnd) : Brick(_cfg, _wnd)
{
	size = 3;
	type = BrickType::EL;
	status = BrickStatus::FALLING;
	shape[0][2] = 1;
	shape[1][0] = 1;
	shape[1][1] = 1;
	shape[1][2] = 1;

}

Brick_El::~Brick_El()
{
}
