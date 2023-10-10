#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <windows.h>

constexpr unsigned int FIRST_GAME_BKG = 4;

const LPCWSTR CONFIG_FILE_NAME = L".\\tetris.ini";

enum class SoundType { NEW_GAME = 0, GAME_OVER = 1, FULL_ROW = 2, ROTATE = 3, MOVE = 4, FAST_FALL = 5, MENU = 6 };
// mixkit.co/free-sound-effects/discover/fast/ 

enum class TextureType {BRICK = 0, START_BKG = 1, LEADERBOARD_BKG = 2, MENU_BKG = 3, OPTIONS_BKG = 3, GAME_BKG_01 = 4, GAME_BKG_02, GAME_BKG_03};

enum ConfigOption { SOUND_EFFECT, MUSIC, GHOST_BRICK, PREVIEW_NEXT_BRICK };

enum LogLevel { NONE = 0, INFO = 1, DEBUG = 2};

struct Result_item {

	std::string name;
	int points;

};

struct  ConfigItem {

	std::string label;
	bool value;
};


class Config
{

	ConfigItem items[5];
	//std::vector<std::string> background_files;
	sf::Music music;
	sf::Font font;
	sf::SoundBuffer sounds[7];
	sf::Sound effect;
	sf::Texture textures[7];

	LogLevel log_level = LogLevel::NONE;

	std::string read_cfg(LPCWSTR _section, LPCWSTR _key, LPCWSTR _default);
	int read_cfg(LPCWSTR _section, LPCWSTR _key, int _default);
	void write_cfg(LPCWSTR _section, LPCWSTR _key, std::string _value);
	void write_cfg(LPCWSTR _section, LPCWSTR _key, int _value);

	void load_effect(SoundType _effect, std::string _file);
	void load_texture(TextureType _effect, std::string _file);

public:
	Result_item leaderboard[5];

	Config();

	std::string get_label(ConfigOption _opt);
	bool is_on(ConfigOption _opt);
	void set(ConfigOption _opt, bool _value);
	void toogle(ConfigOption _opt);

	void save_options();
	void save_results();

	sf::Font& get_font();
	sf::Music& get_music();
	sf::Sound& get_sound(SoundType _type);
	sf::Texture& get_texture(TextureType _type);

	const void Error(std::string _title, std::string _msg);
	const void Log(LogLevel _mode, std::string _title, std::string _msg);


};

