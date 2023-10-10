#include "game.h"
#include <iostream>


Game::Game()
{
	srand((unsigned)time(NULL));

	game_wnd = new sf::RenderWindow(sf::VideoMode(800, 600), "Tetris", sf::Style::None);
	board_wnd = new Board(game_wnd);
	scoreboard_wnd = new Scoreboard(&config, game_wnd);
	preview_wnd = new Preview(&config, game_wnd);
	message_wnd = new Message(&config, game_wnd);

	menu_wnd = new Menu(&config, game_wnd, 400, 300);
	options_wnd = new Options(&config, game_wnd, 800, 600);
	start_wnd = new Start_screen(&config, game_wnd, 800, 600);
	leaderboard_wnd = new Leaderboard(&config, game_wnd, 800, 600);

	//init();
	active_wnd = ActiveWindow::START;

	if (config.is_on(ConfigOption::MUSIC) )//&& config.get_music().getStatus() != sf::Music::Status::Playing)
		config.get_music().play();

}

Game:: ~Game()
{
	delete board_wnd;
	delete scoreboard_wnd;
	delete preview_wnd;
	delete message_wnd;
	delete menu_wnd;
	delete options_wnd;
	delete start_wnd;

	delete game_wnd;
}

void Game::init()
{
	points = 0;
	level = 1;
	game_speed = GAME_SPEED;
	
	game_status = GameStatus::IN_PROGRESS;
	bricks.clear();
	bricks_not_used.clear();

	active_brick = NULL;
	ghost_brick = NULL;
	preview_brick = NULL;
	
	board_wnd->init();
	set_background((int)TextureType::GAME_BKG_01);


	play_effect(SoundType::NEW_GAME);
	config.Log(LogLevel::INFO, "Game", "New game started.");

}

void Game::create_preview_brick(int _arg)
{
	int temp = (_arg == -1)?rand()%7:_arg;
	
	if (preview_brick != NULL && _arg == -1)
		return;

	switch (temp) {
	case 0:
		preview_brick = new Brick_Straight(&config, game_wnd);
		break;
	case 1: 
		preview_brick = new Brick_Square(&config, game_wnd);
		break;
	case 2:
		preview_brick = new Brick_Tee(&config, game_wnd);
		break;
	case 3:
		preview_brick = new Brick_Jay(&config, game_wnd);
		break;
	case 4:
		preview_brick = new Brick_Skewz(&config, game_wnd);
		break;
	case 5:
		preview_brick = new Brick_El(&config, game_wnd);
		break;
	case 6:
		preview_brick = new Brick_Skews(&config, game_wnd);
		break;
	}

	preview_brick->set_color(palette[rand() % MAX_BRICK_COLORS + (int)Colors::BRICK]);
	config.Log(LogLevel::DEBUG, "Game", "Preview brick created.");

}

Brick* Game::create_ghost_brick(Brick* _brick)
{

	Brick* temp = NULL;

	if (active_brick == NULL)
		return NULL;

	temp = new Brick(*active_brick);
	temp->set_status(BrickStatus::GHOST);
	temp->set_color(palette[(int)Colors::GHOST]);

	config.Log(LogLevel::DEBUG, "Game", "Ghost brick created.");
	return temp;
}

void Game::sync_ghost_brick(Brick* _brick)
{
	if (ghost_brick == NULL || _brick == NULL)
		return ;

	ghost_brick->set_pos_x(_brick->get_pos_x());
	char* board = board_wnd->get_row();

	for (int step = _brick->get_pos_y(); step < ROWS; step++)
	{
		ghost_brick->set_pos_y(step);
		for (int row = 0; row < MAX_BRICK_SIZE; row++)
			for (int col = 0; col < MAX_BRICK_SIZE; col++)
				if (ghost_brick->get_shape(col, row) == 1 && *(board + (ghost_brick->get_pos_x() + col) + (ghost_brick->get_pos_y() + row) * (COLUMNS + 1)) > 0)
				{
					ghost_brick->set_pos_y(step-1);
					return;
				}
	}
}

void Game::add_brick_to_board()
{
	if (active_brick == NULL && preview_brick != NULL)
	{
		bricks.push_back(preview_brick);
		active_brick = preview_brick;
		preview_brick = NULL;

		ghost_brick = create_ghost_brick(active_brick);
		sync_ghost_brick(active_brick);
	}
}

void Game::redraw_bricks()
{
	for (Brick* b : bricks)
	{
		b->draw();
	}
	
	if (ghost_brick != NULL && config.is_on(ConfigOption::GHOST_BRICK))
		ghost_brick->draw();

}

void Game::gravity(BrickStatus _status)
{


	if (active_brick!=NULL && active_brick->is_status(_status) && !active_brick->fall_down(board_wnd->get_row()))
	{
		board_wnd->set_busy(active_brick);

		active_brick = NULL;
		delete ghost_brick;
	
		points++;

		check_for_full_rows();
		check_if_game_over();

		add_brick_to_board();
		create_preview_brick();
	}

	clear_empty_bricks();
}
		
void Game::fast_falling()
{
	for (Brick* b : bricks)
	{
		if (b->is_status(BrickStatus::FALLING_FREE) && !b->fall_down(board_wnd->get_row()))
		{
			board_wnd->set_busy(b);
			check_for_full_rows();
		}
	}
}

void Game::brick_fall_faster()
{
	if (active_brick == NULL)
		return;

	play_effect(SoundType::FAST_FALL);
	active_brick->set_status(BrickStatus::FALLING_FAST);
	config.Log(LogLevel::DEBUG, "Game", "Brick started falling fast ..."  + active_brick -> toString());

}

void Game::brick_move_left()
{
	if (active_brick == NULL)
		return;

	play_effect(SoundType::MOVE);
	active_brick->move_left(board_wnd->get_row());
	sync_ghost_brick(active_brick);
	config.Log(LogLevel::DEBUG, "Game", "Brick moved left." + active_brick->toString());


}

void Game::brick_move_right()
{
	if (active_brick == NULL)
		return;

	play_effect(SoundType::MOVE);
	active_brick->move_right(board_wnd->get_row());
	sync_ghost_brick(active_brick);
	config.Log(LogLevel::DEBUG, "Game", "Brick moved right." + active_brick->toString());
	
}

void Game::brick_rotate_right()
{
	if (active_brick == NULL)
		return;

	if (active_brick->rotate_right(board_wnd->get_row()))
	{
		play_effect(SoundType::ROTATE);
		ghost_brick->rotate_right(board_wnd->get_row());
		sync_ghost_brick(active_brick);
		config.Log(LogLevel::DEBUG, "Game", "Brick rotated right." + active_brick->toString());
		message_wnd->set_text("", 1);
	}
}

void Game::brick_rotate_left()
{
	if (active_brick == NULL)
		return;

	if (active_brick->rotate_left(board_wnd->get_row()))
	{
		play_effect(SoundType::ROTATE);
		ghost_brick->rotate_left(board_wnd->get_row());
		sync_ghost_brick(active_brick);
		config.Log(LogLevel::DEBUG, "Game", "Brick rotated left." + active_brick->toString());
		message_wnd->set_text("",1);
	}
}

void Game::check_for_full_rows()
{
	Brick* cloned_brick = NULL;
	
	for (int row = ROWS-1; row >= 0; row--)
	{
		if (board_wnd->is_row_full(row))
		{
			play_effect(SoundType::FULL_ROW);
			points += 100;
			message_wnd->set_text("boom !", 1);
			board_wnd->clear_row(row);

			for (auto itb = bricks.rbegin(); itb != bricks.rend(); itb++)
			{
				if ((*itb)->is_status(BrickStatus::PLACED))
				{
					(*itb)->change_shape(row);

					if ((*itb)->is_empty()) {
						(*itb)->set_status(BrickStatus::EMPTY);
					}

					if ((*itb)->is_split())
					{
						cloned_brick = (*itb)->split_shape();
						bricks.push_back(cloned_brick);
					}
				}
			}		
		}
	}
	sync_ghost_brick(active_brick);
}

void Game::check_if_game_over()
{
	bool result = false;
	Input_box* itxt = NULL;

	for (Brick* b : bricks)
		if (b->is_status(BrickStatus::PLACED))
			if (b->get_pos_y() == 0)
				result = true;

	if (result)
	{
		config.Log(LogLevel::INFO, "Game", "End of game detected ...");
		game_status = GameStatus::GAME_OVER;

		// show & play end game effects
		play_effect(SoundType::GAME_OVER);
		message_wnd->set_text("GAME OVER", 3, true);

		//check if top 5 list should be updated
		for (int i = 0; i < 5; i++)
		{
			if (points > config.leaderboard[i].points)
			{				
				config.Log(LogLevel::INFO, "Game", "Top 5 result achieved ...");

				for (int j = 3; j >= i; j--)
				{
					config.leaderboard[j + 1] = config.leaderboard[j];
				}

				itxt = new Input_box(&config);
				config.leaderboard[i].points = points;
				config.leaderboard[i].name = itxt->get_text();
				delete itxt;
				config.save_results();
				break;
			}
		}

		// go back to startscreen
		menu_wnd->hide();
		start_wnd->show();
		active_wnd = ActiveWindow::START;
	}
}

void Game::clear_empty_bricks()
{
	Brick* tmp;

	for (auto i = bricks.begin(); i != bricks.end();) {
		if ((*i)->is_status(BrickStatus::EMPTY)) {
			tmp = *i;
			i = bricks.erase(i);
			delete tmp;
			config.Log(LogLevel::DEBUG, "Game", "Empty brick removed");
		}
		else
			++i;
	}

}


void Game::set_background(int _index)
{
	background_index = _index;
	background.setTexture(config.get_texture((TextureType)_index));
	background.setPosition(0, 0);
	background.setScale(background.getLocalBounds().width / game_wnd->getSize().x, background.getLocalBounds().height / game_wnd->getSize().y);
	config.Log(LogLevel::DEBUG, "Game", "New background set.");

}

void Game::play_effect(SoundType _type)
{
	if (config.is_on(ConfigOption::SOUND_EFFECT))
	{
		config.get_sound(_type).play();
	}
}

void Game::change_level()
{

	std::string msg;
	level++;
	game_speed -= 30;
	msg = "Level " + std::to_string(level);
	set_background(((++background_index- (int)TextureType::GAME_BKG_01) % 3) + (int)TextureType::GAME_BKG_01);
	message_wnd->set_text(msg, 2);
	config.Log(LogLevel::DEBUG, "Game", "Level changed (" + std::to_string(level) + ")");
}


void Game::play()
{
	sf::Clock gravity_clock;
	sf::Clock fast_clock;
	Input_box*  itxt = NULL;

	
	gravity_clock.restart();


	while (game_wnd->isOpen())
	{
		sf::Event event;

		if ((int)(gravity_clock.getElapsedTime().asMilliseconds()) > game_speed && game_status == GameStatus::IN_PROGRESS)
		{
			gravity(BrickStatus::FALLING);
			gravity_clock.restart();
		}

		if ((int)(fast_clock.getElapsedTime().asMilliseconds()) > (int)(game_speed /13) && game_status == GameStatus::IN_PROGRESS)
		{
			gravity(BrickStatus::FALLING_FAST);
			fast_falling();
			fast_clock.restart();
		}

		if ((level - 1) < (int)(points / LEVEL_UNIT) && game_status == GameStatus::IN_PROGRESS)
		{
			change_level();
		}

		while (game_wnd->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				game_wnd->close();
				break;

			case sf::Event::KeyPressed:

				switch (active_wnd)
				{
					// obsluga klawiatury dla okna startowego
				case ActiveWindow::START:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						play_effect(SoundType::MENU);
						start_wnd->prev_option();
						break;

					case sf::Keyboard::Down:
						play_effect(SoundType::MENU);
 						start_wnd->next_option();
						break;
					
					case sf::Keyboard::Escape:
						return;

					case sf::Keyboard::Enter:
					case sf::Keyboard::Space:
						switch (start_wnd->get_selected())
						{
						case 0:
							start_wnd->hide();
							active_wnd = ActiveWindow::GAME;

							init();
							create_preview_brick();
							add_brick_to_board();
							create_preview_brick();
							break;
						case 1:
							options_wnd->show();
							active_wnd = ActiveWindow::OPTIONS;
							break;
						case 2:
							leaderboard_wnd->show();
							active_wnd = ActiveWindow::LEADERBOARD;
							break;
						case 3:
							return;							
						}
						break;
					}
					break;

				// obsluga klawiatury dla okna z menu
				case ActiveWindow::MENU:
					switch (event.key.code)
					{
					/*case sf::Keyboard::P:
						menu_wnd->hide();
						game_status = GameStatus::IN_PROGRESS;
						active_wnd = ActiveWindow::GAME;
						break;*/
					case sf::Keyboard::Up:
						play_effect(SoundType::MENU);
						menu_wnd->prev_option();
						break;
					case sf::Keyboard::Down:
						play_effect(SoundType::MENU);
						menu_wnd->next_option();
						break;

					case sf::Keyboard::Escape:
						menu_wnd->hide();
						game_status = GameStatus::IN_PROGRESS;
						active_wnd = ActiveWindow::GAME;
						break;
					case sf::Keyboard::Enter:
					case sf::Keyboard::Space:
						switch (menu_wnd->get_selected())
						{
						case 0:
							menu_wnd->hide();
							active_wnd = ActiveWindow::GAME;
							init();
							create_preview_brick();
							add_brick_to_board();
							create_preview_brick();
							break;

						case 1:
							menu_wnd->hide();
							game_status = GameStatus::IN_PROGRESS;
							active_wnd = ActiveWindow::GAME;
							break;

						case 2:
							menu_wnd->hide();
							start_wnd->show();
							active_wnd = ActiveWindow::START;
							break;
						}
						break;
					}
					break;

				// obsluga klawiatury dla okna z najlepszymi wynikami
				case ActiveWindow::LEADERBOARD:
					switch (event.key.code)
					{
						case sf::Keyboard::Enter:
						case sf::Keyboard::Escape:
						case sf::Keyboard::Space:
							leaderboard_wnd->hide();
							start_wnd->show();
							active_wnd = ActiveWindow::START;
							break;
					}
					break;

				// obsluga klawiatury dla okna opcji
				case ActiveWindow::OPTIONS:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						play_effect(SoundType::MENU);
						options_wnd->prev_option();
						break;
					case sf::Keyboard::Down:
						play_effect(SoundType::MENU);
						options_wnd->next_option();
						break;
					case sf::Keyboard::Escape:
						options_wnd->hide();
						start_wnd->show();
						active_wnd = ActiveWindow::START;
						config.save_options();
						break;
					case sf::Keyboard::Enter:
					case sf::Keyboard::Space:
						play_effect(SoundType::MENU);
						switch (options_wnd->get_selected())
						{
						case 0:
							config.toogle(ConfigOption::SOUND_EFFECT);
							break;
						case 1:
							config.toogle(ConfigOption::MUSIC);
							if (!config.is_on(ConfigOption::MUSIC))
							{
								config.get_music().pause();
							}
							else
								config.get_music().play();
							break;
						case 2:
							config.toogle(ConfigOption::GHOST_BRICK);
							break;
						case 3:
							config.toogle(ConfigOption::PREVIEW_NEXT_BRICK);
							break;
						}
						break;
					}
					break;

				// obsluga klawiatury dla okna gry
				case ActiveWindow::GAME:
					switch (event.key.code)
					{

					case sf::Keyboard::Right:
						brick_move_right();
						break;

					case sf::Keyboard::Left:
						brick_move_left();
						break;

					case sf::Keyboard::Space:
						brick_fall_faster();
						fast_clock.restart();
						break;

					case sf::Keyboard::Up:
						brick_rotate_right();
						break;

					case sf::Keyboard::Down:
						brick_rotate_left();
						break;

					case sf::Keyboard::Escape:
					//case sf::Keyboard::P:
						game_status = GameStatus::PAUSED;
						menu_wnd->show();
						active_wnd = ActiveWindow::MENU;
						break;

						// hidden key functions
					case sf::Keyboard::N:
						init();
						create_preview_brick();
						add_brick_to_board();
						create_preview_brick();
						break;

					case sf::Keyboard::M:
						if (config.get_music().getStatus() == sf::Music::Status::Playing)
							config.get_music().pause();
						else
							config.get_music().play();
						break;

					case sf::Keyboard::Num1:
						create_preview_brick(0);
						break;

					case sf::Keyboard::Num2:
						create_preview_brick(1);
						break;

					case sf::Keyboard::Num3:
						create_preview_brick(2);
						break;

					case sf::Keyboard::B:
						//set_background(++background_index % 3);
						set_background(((++background_index - (int)TextureType::GAME_BKG_01) % 3) + (int)TextureType::GAME_BKG_01);

						break;

					case sf::Keyboard::G:
						config.toogle(ConfigOption::GHOST_BRICK);
						break;

					case sf::Keyboard::X:
						config.toogle(ConfigOption::SOUND_EFFECT);
						break;

					case sf::Keyboard::S:
						game_status = GameStatus::GAME_OVER;
						start_wnd->show();
						active_wnd = ActiveWindow::START;
						break;
					}
				}
				break;
			}
		}

		game_wnd->clear();

		game_wnd->draw(background);
		board_wnd->draw();
		
		if (config.is_on(ConfigOption::PREVIEW_NEXT_BRICK))
		{
			preview_wnd->draw(preview_brick);
		}
		scoreboard_wnd->draw(points);
		redraw_bricks();

		start_wnd->draw();
		options_wnd->draw();
		message_wnd->draw();
		menu_wnd->draw();
		leaderboard_wnd->draw();
		
		game_wnd->display();
	}
}


