#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "config.h"
#include "general.h"

class Message
{
	sf::RenderWindow* wnd;

	sf::Text msg_txt;
	sf::Thread thread;

	float time;
	std::string text;

	void set_timer();

public:
	Message(Config* _cfg, sf::RenderWindow* _wnd);
	~Message();
	void draw();
	void set_text(std::string _text);
	void set_text(std::string _text, float _seconds, bool _wait = false);
	void clear_text();
	std::string get_text();
};

