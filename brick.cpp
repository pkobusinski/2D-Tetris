#include "brick.h"



Brick::Brick(Config* _cfg, sf::RenderWindow* _wnd) : 
	cfg(_cfg), wnd(_wnd), size(0), x(4), y(0), type(BrickType::UNKNOWN), status(BrickStatus::UNKNOWN), color(palette[(int)Colors::TRANS])
{

	cell = new sf::RectangleShape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));

	sprite.setTexture(cfg->get_texture(TextureType::BRICK));

	for (int row = 0; row < MAX_BRICK_SIZE; row++)
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
			shape[row][col] = 0;
}

Brick::Brick(const Brick& _brick):
	cfg(_brick.cfg), wnd(_brick.wnd), size(_brick.size), x(_brick.x), y(_brick.y), type(_brick.type), status(_brick.status), color(_brick.color)
{
	cell = new sf::RectangleShape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));

	sprite.setTexture(cfg->get_texture(TextureType::BRICK));

	for (int row = 0; row < MAX_BRICK_SIZE; row++)
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
			shape[row][col] = _brick.shape[row][col];

}

Brick::~Brick()
{
	delete cell;
}


bool Brick::is_status(BrickStatus _status)
{
	return (status == _status);
}

bool Brick::is_empty()
{
	int visible_cells = 0;

	for (int row = 0; row < MAX_BRICK_SIZE; row++)
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
			if (shape[row][col] == 1)
				visible_cells++;

	return visible_cells == 0;
}

bool Brick::is_split()
{
	int total_cell = 0;
	int row_cell = 0;
	int area_cell = 0;

	for (int row = 0; row < MAX_BRICK_SIZE; row++)
	{
		row_cell = 0;
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
		{
			if (shape[row][col] == 1)
			{
				total_cell++;
				row_cell++;
			}
		}

		if (row_cell == 0 && total_cell >0 && area_cell == 0)
		{
			area_cell = total_cell;
		}
	}
	return (area_cell != total_cell && area_cell > 0 );
}


bool Brick::fall_down(char* _row)
{
	for (int row = 0; row < MAX_BRICK_SIZE; row++)
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
		{
			if (shape[row][col] == 1 && *(_row + (x + col) + (y + row + 1) * (COLUMNS + 1)) > 0)
			{
				status = BrickStatus::PLACED;
				return false;
			}
		}
	y++;
	return true;
}

void Brick::move_right(char* _row)
{
	for (int row = 0; row < MAX_BRICK_SIZE; row++)
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
		{
			if (shape[row][col] == 1 && *(_row + (x + col + 1) + (y + row) * (COLUMNS + 1)) > 0)
				return;
		}
	x++;
}

void Brick::move_left(char* _row)
{
	for (int row = 0; row < MAX_BRICK_SIZE; row++)
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
		{
			if (shape[row][col] == 1 && *(_row + (x + col - 1) + (y + row) * (COLUMNS + 1)) > 0)
				return;
		}
	x--;
}


void Brick::rotate( int _size)
{
	for (int row = 0; row < size; row++)
		std::reverse(shape[row], shape[row] + size);

	for (int row = 0; row < size; row++)
		for (int col = row; col < size; col++)
			std::swap(shape[row][col], shape[col][row]);
}

bool Brick::rotate_left(char* _row)
{
	if (status != BrickStatus::GHOST)
	{
		bool empty = true;
		for (int row = 0; row < size; row++)
		{
			if (shape[row][size - 1] == 1)
				empty = false;
		}

		for (int row = 0; row < size; row++)
			for (int col = 0; col < size; col++)
				if (*(_row + (x + col) + (y + row) * (COLUMNS + 1)) > 0)
					return false;
	}

	rotate(size);
	rotate(size);
	rotate(size);

	return true;
}

bool Brick::rotate_right(char* _row)
{
	if (status != BrickStatus::GHOST) 
	{
		bool empty = true;
		for (int row = 0; row < size; row++)
		{
			if (shape[row][size - 1] == 1)
				empty = false;
		}

		for (int row = 0; row < size; row++)
			for (int col = 0; col < size; col++)
				if (*(_row + (x + col) + (y + row) * (COLUMNS + 1)) > 0)
					return false;
	}

	rotate(size);
	return true;
}


void Brick::draw(int _offset_x, int _offset_y)
{
	int offset_x = _offset_x;
	int offset_y = _offset_y;

	if (offset_x == 0 && offset_y == 0)
	{
		offset_x = x * CELL_SIZE;
		offset_y = y * CELL_SIZE;
	}
	for (int row = 0; row < MAX_BRICK_SIZE; row++)
	{
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
		{
			if (shape[row][col] == 1)
			{
				sprite.setPosition((float)(col * CELL_SIZE + offset_x), (float)(row * CELL_SIZE + offset_y));
				wnd->draw(sprite);
			}
		}
	}
}



int Brick::get_pos_x()
{
	return x;
}

void Brick::set_pos_x(int _pos_x)
{
	x = _pos_x;
}

int Brick::get_pos_y()
{
	return y;
}

void Brick::set_pos_y(int _pos_y)
{
	y = _pos_y;
}


char Brick::get_shape(int _x, int _y)
{
	return shape[_y][_x];
}

void Brick::change_shape(int _row)
{
	if (y > _row)
		return;

	if ((int)(y + MAX_BRICK_SIZE) < _row)
	{
		status = BrickStatus::FALLING_FREE;
		return;
	}

	for (int col = 0; col < MAX_BRICK_SIZE; col++)
	{
		if (shape[_row - y][col] == 1)
		{
			shape[_row - y][col] = 0;
		}
	}

	status = BrickStatus::FALLING_FREE;
}

Brick* Brick::split_shape()
{
	int row_cell;
	bool cloned = false;
	Brick* cloned_brick = new Brick(*this);

	for (int row = 0; row < MAX_BRICK_SIZE; row++)
	{
		row_cell = 0;
		for (int col = 0; col < MAX_BRICK_SIZE; col++)
		{
			if (shape[row][col] == 1 && !cloned)
			{
				shape[row][col] = 0;
				row_cell++;
			}
			if (shape[row][col] == 1 && cloned)
			{
				cloned_brick->shape[row][col] = 0;
				row_cell++;
			}
		}
		if (row_cell == 0)
		{
			cloned = true;
		}
	}

	return cloned_brick;
}


BrickType Brick::get_type()
{
	return type;
}

sf::Color Brick::get_color()
{
	return sprite.getColor();
}


void Brick::set_color(sf::Color _color)
{
	sprite.setColor(_color);
}

void Brick::set_status(BrickStatus _new_status)
{
	status = _new_status;
}
