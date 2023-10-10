#pragma once
#include<SFML/Graphics.hpp>
#include <iostream> 
#include <sstream>
#include <algorithm>
#include "general.h"
#include "config.h"

enum class BrickType { UNKNOWN, PREVIEW, STRAIGHT, SQUARE, SKEWS, SKEWZ, JAY, EL, TEE };

enum class BrickStatus { UNKNOWN, FALLING, FALLING_FAST, FALLING_FREE, PLACED, GHOST, EMPTY};

class Brick
{
protected: 
	int x;
	int y; 
	char shape[MAX_BRICK_SIZE][MAX_BRICK_SIZE];
	int size; 
	BrickType type;
	BrickStatus status;

	sf::Color color;
	sf::RenderWindow* wnd;
	sf::RectangleShape* cell;
	sf::Texture texture;
	sf::Sprite sprite; 

	Config* cfg;

	void rotate(int _size);
	void show();
public: 
	Brick(Config* _cfg, sf::RenderWindow* _wnd);
	Brick(const Brick& _brick);
	~Brick();

	void init();
	
	bool is_status(BrickStatus _status);
	bool is_empty();
	bool is_split();

	void move_right(char* _row);
	void move_left(char* _row);
	bool rotate_left(char* _row);
	bool rotate_right(char* _row);
	bool fall_down(char* _row);
	void draw(int _offset_x = 0, int _offset_y = 0);
	
	void change_shape(int _row);
	
	void set_color(sf::Color _color);
	void set_status(BrickStatus _new_status);
	int get_pos_x();
	int get_pos_y();
	void set_pos_x(int _pos_x);
	void set_pos_y(int _pos_y);
	char get_shape(int _x, int _y);
	Brick* split_shape();
	BrickType get_type();
	sf::Color get_color();

	std::string toString() {
		
		std::ostringstream oss;

		std::string type_name = "";
		std::string status_name = "";

		switch (type)
		{
			case BrickType::UNKNOWN: 	type_name = "UNKNOWN";  break;
			case BrickType::STRAIGHT:	type_name = "STRAIGHT";	break;
			case BrickType::SQUARE:		type_name = "SQUARE";	break;
			case BrickType::SKEWS:		type_name = "SKEWS";	break;
			case BrickType::SKEWZ:		type_name = "SKEWZ";	break;
			case BrickType::JAY:		type_name = "JAY";		break;
			case BrickType::EL:			type_name = "EL";		break;
			case BrickType::TEE:		type_name = "TEE";		break;
		}

		switch (status)
		{
			case BrickStatus::UNKNOWN:		status_name = "UNKNOWN";		break;
			case BrickStatus::FALLING:		status_name = "FALLING";		break;
			case BrickStatus::FALLING_FAST:	status_name = "FALLING FAST";	break;
			case BrickStatus::FALLING_FREE:	status_name = "FALLING FREE";	break;
			case BrickStatus::PLACED:		status_name = "PLACED";			break;
			case BrickStatus::GHOST:		status_name = "GHOST";			break;
		}

		oss << "[ " << "& this"
			<< " " << type_name
			<< " " << status_name
			<< " x:" << x
			<< " y:" << y
			<< " ]";

		return oss.str();
	}

	friend std::ostream& operator<<(std::ostream& os, Brick& brick)
	{
		std::string type_name = "";
		std::string status_name = "";

		switch (brick.type)
		{
		case BrickType::UNKNOWN:
			type_name = "UNKNOWN";
			break;
		case BrickType::STRAIGHT:
			type_name = "STRAIGHT";
			break;
		case BrickType::SQUARE:
			type_name = "SQUARE";
			break;
		case BrickType::SKEWS:
			type_name = "SKEWS";
			break;
		case BrickType::SKEWZ:
			type_name = "SKEWZ";
			break;
		case BrickType::JAY:
			type_name = "JAY";
			break;
		case BrickType::EL:
			type_name = "EL";
			break;
		case BrickType::TEE:
			type_name = "TEE";
			break;
		}
		switch (brick.status)
		{
		case BrickStatus::UNKNOWN:
			status_name = "UNKNOWN";
			break;
		case BrickStatus::FALLING:
			status_name = "FALLING";
			break;
		case BrickStatus::FALLING_FAST:
			status_name = "FALLING FAST";
			break;
		case BrickStatus::FALLING_FREE:
			status_name = "FALLING FREE";
			break;
		case BrickStatus::PLACED:
			status_name = "PLACED";
			break;
		case BrickStatus::GHOST:
			status_name = "GHOST";
			break;
		}
		os << "[ " << &brick
			<< " " << type_name
			<< " " << status_name
			<< " x:" << brick.x
			<< " y:" << brick.y
			<< " ]";

		return os;
	}
};
