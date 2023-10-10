#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "general.h"
#include "board.h"
#include "preview.h"
#include "scoreboard.h"
#include "menu.h"
#include "options.h"
#include "message.h"
#include "config.h"
#include "leaderboard.h"
#include "startscreen.h"
#include <vector>
#include <list>
#include "brick.h"
#include "brick_Straight.h"
#include "brick_Skews.h"
#include "brick_Square.h"
#include "brick_Jay.h"
#include "brick_Skewz.h"
#include "brick_El.h"
#include "brick_Tee.h"
#include "input_box.h"

enum class GameStatus {PAUSED, GAME_OVER, IN_PROGRESS };
enum class ActiveWindow { GAME, START, MENU, OPTIONS, LEADERBOARD, INPUT_TEXT };

class Game{

	Board* board_wnd;
	Preview* preview_wnd;
	Scoreboard* scoreboard_wnd;
	Message* message_wnd;
	Menu* menu_wnd;
	Options* options_wnd;
	Start_screen* start_wnd;
	Leaderboard* leaderboard_wnd;

	Config config;
	int points;
	int level;
	int number_of_lines_cleared;
	int game_speed;

	
	GameStatus game_status;
	ActiveWindow active_wnd;

	sf::RenderWindow* game_wnd;
	std::list<Brick*> bricks;
	std::list<Brick*> bricks_not_used;

	Brick* preview_brick;
	Brick* active_brick;
	Brick* ghost_brick;

	sf::Sprite background;
	sf::Texture background_image;
	std::vector<std::string> background_files;
	int background_index;

	void init();
	void set_background(int _index);
	void play_effect(SoundType _type);
	void change_level();

	void create_preview_brick(int _arg=-1);
	Brick* create_ghost_brick(Brick* _brick);
	void clear_empty_bricks();

	void add_brick_to_board();
	void redraw_bricks();
	void sync_ghost_brick(Brick* _brick);

	void gravity(BrickStatus _status);
	void fast_falling();
	void brick_fall_faster();
	void check_for_full_rows();
	void check_if_game_over();

	void brick_move_right();
	void brick_move_left();
	void brick_rotate_left();
	void brick_rotate_right();

	
public: 
	Game();
	~Game();
	void play();

	
	
};

