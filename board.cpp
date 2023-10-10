#include "board.h"

Board::Board(sf::RenderWindow* _wnd) : wnd(_wnd)
{
	init();
}

Board::~Board()
{
}

void Board::draw()
{
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
	cell.setFillColor(palette[(int)Colors::BOARD]);
	
	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < COLUMNS; col++)
		{
			cell.setPosition((float)(CELL_SIZE * col),(float) (CELL_SIZE * row));
			wnd->draw(cell);
		}
}

void Board::set_busy(Brick* _brick)
{
	for (int i = 0; i < MAX_BRICK_SIZE; i++)
	{
		for (int j = 0; j < MAX_BRICK_SIZE; j++)
		{
			if (_brick->get_shape(i,j) == 1)
			{
				board_matrix[_brick->get_pos_y() + j][_brick->get_pos_x() + i]= 1;
			}
		}
	}
}

bool Board::is_row_full(int _row)
{
	for (int col = 0; col < COLUMNS; col++)
	{
		if (board_matrix[_row][col] != 1)
			return false;
	}

	return true;
}

char* Board::get_row()
{
	return &board_matrix[0][0];
}

void Board::clear_row(int _row)
{
	for(int row=0; row<=_row; row++)
		for (int col = 0; col < COLUMNS; col++)
		{
			board_matrix[row][col] = 0;
		}
}

void Board::init()
{
	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < COLUMNS; col++)
			board_matrix[row][col] = 0;

	for (int col = 0; col < COLUMNS + 1; col++)
		board_matrix[ROWS][col] = 2;

	for (int row = 0; row < ROWS; row++)
		board_matrix[row][COLUMNS] = 2;
}
