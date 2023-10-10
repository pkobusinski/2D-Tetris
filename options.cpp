#include "options.h"

Options::Options(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height) : Dlg_window(_cfg, _wnd, _width, _height)
{
	max_lines = 4;

	lines[0].label = _cfg->get_label(ConfigOption::SOUND_EFFECT);
	lines[1].label = _cfg->get_label(ConfigOption::MUSIC); 
	lines[2].label = _cfg->get_label(ConfigOption::GHOST_BRICK); 
	lines[3].label = _cfg->get_label(ConfigOption::PREVIEW_NEXT_BRICK);

	background.setTexture(cfg->get_texture(TextureType::OPTIONS_BKG));
	set_header("Options");
	set_footer("Press ESC to go back ...",30);

	for (int i = 0; i < max_lines; i++)
	{
		lines[i].field_1.setString(lines[i].label);
		lines[i].field_1.setCharacterSize(45);
		lines[i].field_1.setFillColor(palette[(int)Colors::TEXT]);
		lines[i].field_1.setPosition(frame.getPosition().x + 120, frame.getPosition().y + 150 + 85 * i);
		lines[i].field_1.setFont(cfg->get_font());
		
		lines[i].checkbox.setOutlineColor(palette[(int)Colors::ITEM]);
		lines[i].checkbox.setFillColor(palette[(int)Colors::TRANS]);
		lines[i].checkbox.setOutlineThickness (3);
		lines[i].checkbox.setSize(sf::Vector2f(15, 15));
		lines[i].checkbox.setPosition(frame.getPosition().x + 70, frame.getPosition().y + 170 + 85 * i);
	}
}

Options::~Options()
{
}

void Options::draw()
{
	if (visible)
	{
		Dlg_window::draw();

		lines[0].value = cfg->is_on(ConfigOption::SOUND_EFFECT);
		lines[1].value = cfg->is_on(ConfigOption::MUSIC);
		lines[2].value = cfg->is_on(ConfigOption::GHOST_BRICK);
		lines[3].value = cfg->is_on(ConfigOption::PREVIEW_NEXT_BRICK);

		for (int i = 0; i < max_lines; i++)
		{
			lines[i].field_1.setFillColor((selected_line == i) ? palette[(int)Colors::TEXT_ACTIVE] : palette[(int)Colors::TEXT]);
			lines[i].checkbox.setFillColor(lines[i].value ? palette[(int)Colors::ITEM_ACTIVE] : palette[(int)Colors::TRANS]);
			wnd->draw(lines[i].field_1);
			wnd->draw(lines[i].checkbox);
		}
	}
}