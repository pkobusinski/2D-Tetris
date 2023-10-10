#include "dlg_window.h"

Dlg_window::Dlg_window(Config* _cfg, sf::RenderWindow* _wnd, float _width, float _height) : 
	cfg(_cfg), wnd(_wnd), width(_width), height(_height), visible(false), selected_line(0), max_lines(0)
{
	
	frame.setSize(sf::Vector2f(width, height));
	frame.setPosition(wnd->getSize().x / 2 - width / 2, wnd->getSize().y / 2 - height / 2);
	frame.setOutlineThickness(1.0f);
	frame.setOutlineColor(palette[(int)Colors::TEXT]);
	frame.setFillColor(palette[(int)Colors::TRANS]);

	background.setPosition(wnd->getSize().x / 2 - width / 2, wnd->getSize().y / 2 - height / 2);
	background.setScale(_width / wnd->getSize().x, _height / wnd->getSize().y);

	header.setFont(cfg->get_font());
	header.setFillColor(palette[(int)Colors::TEXT]);
	header.setPosition(frame.getPosition().x + 10, frame.getPosition().y + 10);
	header.setString("");

	footer.setFont(cfg->get_font());
	footer.setFillColor(palette[(int)Colors::TEXT]);
	footer.setPosition(frame.getPosition().x + 10, frame.getPosition().y + 10);
	footer.setCharacterSize(20);
	footer.setString("");
}


Dlg_window::~Dlg_window()
{
}

void Dlg_window::show()
{
	visible = true;
	draw();
}

void Dlg_window::hide()
{
	visible = false;
}

bool Dlg_window::is_visible()
{
	return visible;
}

void Dlg_window::set_header(std::string _title, int _font_size)
{
	header.setCharacterSize(_font_size);
	header.setString(_title);
	header.setPosition(frame.getPosition().x + (width - header.getLocalBounds().width) / 2, frame.getPosition().y + 10);
}

void Dlg_window::set_footer(std::string _title, int _font_size)
{
	footer.setCharacterSize(_font_size);
	footer.setString(_title);
	footer.setPosition(frame.getPosition().x + (width - footer.getLocalBounds().width) - 20, frame.getPosition().y + height - 50);
}

void Dlg_window::draw()
{
	if (visible)
	{
		wnd->draw(background);
		wnd->draw(frame);

		if (header.getString() != "") 
			wnd->draw(header);

		if (footer.getString() != "")
			wnd->draw(footer);
	}
}

void Dlg_window::prev_option()
{
	selected_line = (selected_line +max_lines - 1)%max_lines;
}

void Dlg_window::next_option()
{
	selected_line = (selected_line + 1) % max_lines;
}


int Dlg_window::get_selected()
{
	return selected_line;
}
