#include "message.h"

Message::Message(Config* _cfg, sf::RenderWindow* _wnd) : thread(&Message::set_timer, this)
{
	wnd = _wnd;
	
	text = "";

	msg_txt.setFont(_cfg->get_font());
	msg_txt.setCharacterSize(70);
	msg_txt.setFillColor(palette[(int)Colors::TEXT_ACTIVE]);
}

Message::~Message()
{
}

void Message::set_text(std::string _text)
{
	text = _text;
}

void Message::set_text(std::string _text, float _seconds, bool _wait)
{
	text = _text;
	time = _seconds;
	thread.terminate();
	thread.launch();

	if (_wait) {
		draw();
		wnd->display();
		thread.wait();
	}
}

void Message::set_timer()
{
	sf::sleep(sf::seconds(time));
	clear_text();
}

void Message::clear_text()
{
	text = "";
	time = 0.0f;
}

std::string Message::get_text()
{
	return text;
}


void Message::draw()
{
	if (text == "")
		return;

	msg_txt.setString(text);
	msg_txt.setPosition((wnd->getSize().x - msg_txt.getLocalBounds().width) /2, 200);

	wnd->draw(msg_txt);
}