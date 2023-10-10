#include "leaderboard.h"

Leaderboard::Leaderboard(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height) : Dlg_window(_cfg, _wnd, _width, _height)
{

	background.setTexture(cfg->get_texture(TextureType::LEADERBOARD_BKG));
	set_header("TOP 5");
	set_footer("Press ESC to go back ...",30);


	for (int i = 0; i < LEADERBOARD_MAX_ITEM; i++)
	{
		lines[i].field_1.setCharacterSize(45);
		lines[i].field_1.setFillColor(palette[(int)Colors::TEXT]);
		lines[i].field_1.setPosition(frame.getPosition().x + 160, frame.getPosition().y + 120 + 80 * i);
		lines[i].field_1.setFont(_cfg->get_font());

		lines[i].field_2.setCharacterSize(45);
		lines[i].field_2.setFillColor(palette[(int)Colors::TEXT]);
		lines[i].field_2.setPosition(frame.getPosition().x + 480, frame.getPosition().y + 120 + 80 * i);
		lines[i].field_2.setFont(_cfg->get_font());
	}
}

void Leaderboard::draw()
{
	if (visible)
	{
		Dlg_window::draw();

		for (int i = 0; i < 5; i++)
		{
			lines[i].field_1.setString(cfg->leaderboard[i].name);
			lines[i].field_2.setString(std::to_string(cfg->leaderboard[i].points));		
			lines[i].field_2.setPosition(frame.getPosition().x + 480 + (125 - lines[i].field_2.getLocalBounds().width), lines[i].field_2.getPosition().y);
			
			wnd->draw(lines[i].field_1);
			wnd->draw(lines[i].field_2);
		}

	}
}