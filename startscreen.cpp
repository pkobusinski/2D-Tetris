#include "startscreen.h"

Start_screen::Start_screen(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height) :Dlg_window(_cfg, _wnd, _width, _height)
{
	visible = true;
	max_lines = 4;

	background.setTexture(cfg->get_texture(TextureType::START_BKG));
	background.setPosition(0, 0);

	set_footer("(c) Hubert Blaszczyk Piotr Kobusinski '2023");

	lines[0].label = "New Game";
	lines[1].label = "Options";
	lines[2].label = "Top results";
	lines[3].label = "Exit";

	for (int i = 0; i < max_lines; i++)
	{
		lines[i].field_1.setString(lines[i].label);
		lines[i].field_1.setCharacterSize(100);
		lines[i].field_1.setFillColor(palette[(int)Colors::TEXT]);
		lines[i].field_1.setPosition(frame.getPosition().x + 100, frame.getPosition().y + 65 + 120 * i);
		lines[i].field_1.setFont(cfg->get_font());
	}
}

void Start_screen::draw()
{
	if (visible)
	{	
		Dlg_window::draw();

		for (int i = 0; i < max_lines; i++)
		{
			lines[i].field_1.setFillColor((selected_line == i) ? palette[(int)Colors::TEXT_ACTIVE] : palette[(int)Colors::TEXT]);
			wnd->draw(lines[i].field_1);
		}
	}
}