#include "menu.h"

Menu::Menu(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height) : Dlg_window(_cfg, _wnd, _width, _height)
{

	max_lines = 3;

	lines[0].label = "New game";
	lines[1].label = "Resume game";
	lines[2].label = "End game";

	background.setTexture(cfg->get_texture(TextureType::MENU_BKG));

	set_header("Menu", 50);
	set_footer("Press ESC to go back ...");

	for (int i = 0; i < max_lines; i++)
	{
		lines[i].field_1.setString(lines[i].label);
		lines[i].field_1.setCharacterSize(30);
		lines[i].field_1.setFillColor(palette[(int)Colors::TEXT]);
		lines[i].field_1.setPosition(frame.getPosition().x +30, frame.getPosition().y + 85+ 50 * i);
		lines[i].field_1.setFont(cfg->get_font());		
	}
}

void Menu::draw()
{
	if (is_visible())
	{
		Dlg_window::draw();

		for (int i = 0; i < max_lines; i++)
		{
			lines[i].field_1.setFillColor((selected_line == i) ? palette[(int)Colors::TEXT_ACTIVE]: palette[(int)Colors::TEXT]);
			wnd->draw(lines[i].field_1);
		}
	}
}