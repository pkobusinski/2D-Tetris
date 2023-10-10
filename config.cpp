#include "config.h"
#include <iostream>

Config::Config()
{
	log_level = LogLevel::INFO;

	// settings initialization
	items[ConfigOption::SOUND_EFFECT]	= { "sound effect", read_cfg(L"Options", L"sound_effect", 0) == 1 };
	items[ConfigOption::MUSIC]			= { "music",  read_cfg(L"Options", L"music", 0) == 1 };
	items[ConfigOption::GHOST_BRICK]	= { "ghost brick",  read_cfg(L"Options", L"ghost_brick", 0) == 1 };
	items[ConfigOption::PREVIEW_NEXT_BRICK] = { "preview next brick",  read_cfg(L"Options", L"preview_next_brick", 0) == 1 };

	Log(LogLevel::DEBUG, "Config", "Initialization of settings succesful.");

	// graphics initialization
	load_texture(TextureType::BRICK, read_cfg(L"Graphics", L"brick", L""));
	load_texture(TextureType::START_BKG, read_cfg(L"Graphics", L"startscreen", L""));
	load_texture(TextureType::LEADERBOARD_BKG, read_cfg(L"Graphics", L"leaderboard", L""));
	load_texture(TextureType::MENU_BKG, read_cfg(L"Graphics", L"menu", L""));
	load_texture(TextureType::OPTIONS_BKG, read_cfg(L"Graphics", L"options", L""));
	load_texture(TextureType::GAME_BKG_01, read_cfg(L"Graphics", L"game_bkg_01", L""));
	load_texture(TextureType::GAME_BKG_02, read_cfg(L"Graphics", L"game_bkg_02", L""));
	load_texture(TextureType::GAME_BKG_03, read_cfg(L"Graphics", L"game_bkg_03", L""));

	Log(LogLevel::DEBUG, "Config", "Initialization of graphics finised succesful.");

	// sound effect initialization
	load_effect(SoundType::FAST_FALL, read_cfg(L"Effects", L"fast_fall", L""));
	load_effect(SoundType::FULL_ROW, read_cfg(L"Effects", L"full_row", L""));
	load_effect(SoundType::GAME_OVER, read_cfg(L"Effects", L"game_over", L""));
	load_effect(SoundType::MENU, read_cfg(L"Effects", L"menu", L""));
	load_effect(SoundType::MOVE, read_cfg(L"Effects", L"movement", L""));
	load_effect(SoundType::NEW_GAME, read_cfg(L"Effects", L"new_game", L""));
	load_effect(SoundType::ROTATE, read_cfg(L"Effects", L"rotation", L""));

	effect.setVolume(100);
	Log(LogLevel::DEBUG, "Config", "Initialization of sound effects finised succesful.");



	// music initialization
	if (!music.openFromFile(read_cfg(L"Music", L"file", L""))) {
		Config::Error("Sound", "music file loading error ...");
		exit(-1);
	}
	music.setLoop(true);
	music.setVolume(40);
	Log(LogLevel::DEBUG, "Config", "Initialization of music finised succesfully.");


	if (!font.loadFromFile(read_cfg(L"Fonts", L"file", L"")))
	{
		Config::Error("Font", "font file loading error ...");
		exit(-1);
	}
	Log(LogLevel::DEBUG, "Config", "Initialization of fonts finised succesfully.");


	// initialize top 5 result list
	wchar_t buf[255];
	for (int i = 0; i < 5; i++)
	{
		wsprintfW(buf, L"%d_name", i+1);
		leaderboard[i].name = read_cfg(L"Results", buf, L"---");

		wsprintfW(buf, L"%d_points", i+1);
		leaderboard[i].points = read_cfg(L"Results", buf, 0);;
	}
	Log(LogLevel::DEBUG, "Config", "Initialization of fonts finised succesfully.");

	Log(LogLevel::INFO, "Config", "Configuration reading completed.");
}

void Config::load_effect(SoundType _effect, std::string _file)
{
	if (!sounds[(int)_effect].loadFromFile(_file))
	{
		Error("Sound", "sound effect file loading error ...");
		exit(-1);
	}
}

void Config::load_texture(TextureType _texture, std::string _file)
{
	if (_texture == TextureType::BRICK)
	{
		if (!textures[(int) _texture].loadFromFile(_file, sf::IntRect(0, 0, 30, 30)))
		{
			Error("Graphics", "texture file loading error ...");
			exit(-1);
		}
	}
	else
	{
		if (!textures[(int)_texture].loadFromFile(_file))
		{
			Error("Graphics", "background graphics file loading error ...");
			exit(-1);
		}
	}
}

const void Config::Error(std::string _title, std::string _msg)
{
	std::cerr << _title << ": " << _msg << std::endl;
}

const void Config::Log(LogLevel _mode, std::string _title, std::string _msg)
{
	if (_mode <= log_level)
		std::clog << _title << ": " << _msg << std::endl;
}

sf::Font& Config::get_font()
{
	return font;
}

sf::Music& Config::get_music()
{
	return music;
}


sf::Sound& Config::get_sound(SoundType _type)
{
	effect.setBuffer(sounds[(int)_type]);
	return effect;
}

sf::Texture& Config::get_texture(TextureType _type)
{
	return textures[(int)_type];
}

std::string Config::get_label(ConfigOption _opt)
{
	return items[_opt].label;
}

bool Config::is_on(ConfigOption _opt)
{
	return items[_opt].value;
}

void Config::set(ConfigOption _opt, bool _value)
{
	items[_opt].value = _value;
}

void Config::toogle(ConfigOption _opt)
{
	items[_opt].value = !items[_opt].value;
}

std::string Config::read_cfg(LPCWSTR _section, LPCWSTR _key, LPCWSTR _default)
{
	wchar_t value[255];
	GetPrivateProfileString(_section, _key, _default, value, 255, CONFIG_FILE_NAME);
	std::wstring ws(value);
	std::string str(ws.begin(), ws.end());
	Log(LogLevel::DEBUG, "Config", "Read string from INI file. ["+str+"]");
	return str;
}

void Config::write_cfg(LPCWSTR _section, LPCWSTR _key, std::string _value)
{
	wchar_t buf[255];
	wsprintfW(buf, L"%hs", _value.c_str());

	WritePrivateProfileString(_section, _key, buf, L".\\tetris.ini");
	Log(LogLevel::DEBUG, "Config", "Wrote string to INI file. [" + _value + "]");
}

int Config::read_cfg(LPCWSTR _section, LPCWSTR _key, int _default)
{
	int value = GetPrivateProfileInt(_section, _key, _default, CONFIG_FILE_NAME);
	Log(LogLevel::DEBUG, "Config", "Read value from INI file. [" + std::to_string(value) + "]");
	return value;
}

void Config::write_cfg(LPCWSTR _section, LPCWSTR _key, int _value)
{
	wchar_t buf[255];
	wsprintfW(buf, L"%d", _value);
	WritePrivateProfileString(_section, _key, buf, L".\\tetris.ini");
	Log(LogLevel::DEBUG, "Config", "Wrote value to INI file. [" + std::to_string(_value) + "]");
}

void Config::save_options()
{
	write_cfg(L"Options", L"sound_effect", items[ConfigOption::SOUND_EFFECT].value);
	write_cfg(L"Options", L"music", items[ConfigOption::MUSIC].value);
	write_cfg(L"Options", L"ghost_brick", items[ConfigOption::GHOST_BRICK].value);
	write_cfg(L"Options", L"preview_next_brick", items[ConfigOption::PREVIEW_NEXT_BRICK].value);

	Log(LogLevel::DEBUG, "Config", "Settings saved.");
}

void Config::save_results()
{
	wchar_t buf[255];
	for (int i = 0; i < 5; i++)
	{
		wsprintfW(buf, L"%d_name", i+1);
		write_cfg(L"Results", buf, leaderboard[i].name);
		wsprintfW(buf, L"%d_points", i+1);
		write_cfg(L"Results", buf, leaderboard[i].points);
	}
	Log(LogLevel::DEBUG, "Config", "Top 5 result list saved.");

}

