#include "input_box.h"

Input_box::Input_box(Config* _cfg)
{
	input_box_wnd = new sf::RenderWindow(sf::VideoMode(450, 230), "", sf::Style::None);

	frame.setSize(sf::Vector2f(input_box_wnd->getSize().x-2.0f, input_box_wnd->getSize().y-2.0f));
	frame.setOutlineThickness(1.0f);
	frame.setOutlineColor(palette[(int)Colors::TEXT]);
	frame.setFillColor(palette[(int)Colors::TRANS]);
	frame.setPosition(1, 1);

	label.setFont(_cfg->get_font());
	label.setCharacterSize(30);
	label.setFillColor(palette[(int)Colors::TEXT]);
	label.setPosition(25, 30);
	label.setString("      Congratulations !\nYou achieved one of the\n            top 5 results.\n \nEnter user name:");

	input_field.setSize(sf::Vector2f(400, 50));
	input_field.setFillColor(palette[(int)Colors::OVERLAY_BACKGROUND]);
	input_field.setPosition(25, 170);

	input_txt.setFont(_cfg->get_font());
	input_txt.setCharacterSize(40);
	input_txt.setFillColor(palette[(int)Colors::TEXT_ACTIVE]);
	input_txt.setPosition(30, 170);
	input_txt.setString("");

	draw();

	while (input_box_wnd->isOpen())
	{
		sf::Event event;

		while (input_box_wnd->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				input_box_wnd->close();
				return;
			case sf::Event::TextEntered:
				if (std::isprint(event.text.unicode) && text.length() < 10)
					text += event.text.unicode;
				draw();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::BackSpace:
					if (!text.empty())
						text.pop_back();
					draw();
					break;

				case sf::Keyboard::Return:
					input_box_wnd->close(); 
					return;
				}
			}
		}
	}
};

Input_box::~Input_box()
{
	delete input_box_wnd;
}

std::string Input_box::get_text()
{
	return text;
}

void Input_box::draw()
{
	input_box_wnd->clear();

	input_txt.setString(text);

	input_box_wnd->draw(frame);
	input_box_wnd->draw(label);
	input_box_wnd->draw(input_field);
	input_box_wnd->draw(input_txt);

	input_box_wnd->display();
}