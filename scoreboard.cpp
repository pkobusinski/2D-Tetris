////////////////////////////////////////////////////////////////////////////////////////////////////
/// File:	tetris2\scoreboard.cpp.
///
/// Summary:	Implements the scoreboard class.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "scoreboard.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Scoreboard::Scoreboard
///
/// Summary:	Constructor.
///
/// Author:	Piotr Kobusinski
///
/// Date:	22.01.2023
///
/// Parameters:
/// _cfg - 	   	[in,out] If non-null, the configuration.
/// _wnd - 	   	[in,out] If non-null, the window.
////////////////////////////////////////////////////////////////////////////////////////////////////

Scoreboard::Scoreboard(Config* _cfg, sf::RenderWindow* _wnd)
{	
	wnd = _wnd;

	score_wnd.setSize(sf::Vector2f(280, 60));
	score_wnd.setPosition(420, 60);
	score_wnd.setFillColor(palette[(int)Colors::BACKGROUND]);

	score_txt.setFont(_cfg->get_font());
	score_txt.setString("Score: ");
	score_txt.setCharacterSize(35);
	score_txt.setFillColor(palette[(int)Colors::TEXT_ACTIVE]);
	score_txt.setPosition(420, 20);


	score_value.setFont(_cfg->get_font());
	score_value.setCharacterSize(35);
	score_value.setFillColor(palette[(int)Colors::TEXT]);
	score_value.setPosition(430, 65);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Scoreboard::~Scoreboard
///
/// Summary:	Destructor.
///
/// Author:	Piotr Kobusinski
///
/// Date:	22.01.2023
////////////////////////////////////////////////////////////////////////////////////////////////////

Scoreboard::~Scoreboard()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function:	Scoreboard::draw
///
/// Summary:	Draws.
///
/// Author:	Piotr Kobusinski
///
/// Date:	22.01.2023
///
/// Parameters:
/// _points - 	The points to be presented.
////////////////////////////////////////////////////////////////////////////////////////////////////

void Scoreboard::draw(int _points)
{
	std::string value_str =	std::to_string(_points);
	score_value.setString(value_str);

	wnd->draw(score_wnd);
	wnd->draw(score_txt);
	wnd->draw(score_value);

}