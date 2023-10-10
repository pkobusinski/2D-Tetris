#include "preview.h"

Preview::Preview(Config* _cfg, sf::RenderWindow* _wnd)
{
	wnd = _wnd;
	
	prev_wnd.setSize(sf::Vector2f(280, 180));
	prev_wnd.setPosition(420, 350);
	prev_wnd.setFillColor(palette[(int)Colors::BACKGROUND]);

	prev_txt.setFont(_cfg->get_font());
	prev_txt.setString("Next shape: ");
	prev_txt.setCharacterSize(30);
	prev_txt.setFillColor(palette[(int)Colors::TEXT_ACTIVE]);
	prev_txt.setPosition(420, 315);

}

Preview::~Preview()
{
}

void Preview::draw(Brick* next_brick)
{
	wnd->draw(prev_txt);
	wnd->draw(prev_wnd);
	if (next_brick != NULL)
	{
		next_brick->draw(520, 400);
	}
}