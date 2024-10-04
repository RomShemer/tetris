#include "tetromino.h"
#include "general.h"
#include <windows.h>
#include <iostream>
using namespace std;

#define EMPTY -1
#define BLOCK_INDEX_CENTER -1

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

//int Tetromino::probCounter = 0;

/*This function returns the array of Point objects representing the tetromino's shape.*/
const Point* Tetromino::getShapeArr()const
{
	return shape;
}


/*This function returns the background color of the tetromino.*/
int Tetromino::getColor()const
{
	return backgroundcolor;
}

/*This function returns the character representation of the tetromino's shape.*/
char Tetromino::getShapeChar()const
{
	return ch;
}


/*This function returns the type of the tetromino.*/
GameConfig::TetrisShapes Tetromino::getType()const
{
	return type;
}


/*This function returns the index of the center block in the tetromino.*/
int Tetromino::getIndexCenter()const
{
	return indexCenter;
}


/*This function returns the number of times the tetromino has been rotated.*/
int Tetromino::getTimesOfRotations()const
{
	return timesOfRotation;
}


/*This function sets the background color of the tetromino based on the IsWithColor parameter.*/
void Tetromino::SetColor(bool IsWithColor)
{

	if (IsWithColor == false)
	{
		this->backgroundcolor = GameConfig::COLORS[0];

	}
	else
	{
		this->backgroundcolor = 1;
	}
}


/*This function moves and rotates the tetromino based on the key pressed and player index
* Only if Realmove=ture the function delete the shape from board (replace it with empty point print) */
void Tetromino::move(const int keypressed, const GameConfig::PlayerIndex indexPlayer, bool RealMove)
{
	bool noRotate = false;

	if (RealMove)
	{
		shape[0].setColor(GameConfig::COLORS[0]);
		shape[1].setColor(GameConfig::COLORS[0]);
		shape[2].setColor(GameConfig::COLORS[0]);
		shape[3].setColor(GameConfig::COLORS[0]);


		shape[0].draw(' ', indexPlayer);
		shape[1].draw(' ', indexPlayer);
		shape[2].draw(' ', indexPlayer);
		shape[3].draw(' ', indexPlayer);
	}
	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
	{
		GameConfig::eKeys_LeftPlayer direction = (GameConfig::eKeys_LeftPlayer)keypressed;
		if (GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1 == direction || GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE2 == direction)
		{
			if (indexCenter != BLOCK_INDEX_CENTER)
			{
				RotateClock(shape[indexCenter].getX(), shape[indexCenter].getY());
				timesOfRotation++;
			}
		}
		else if (GameConfig::eKeys_LeftPlayer::ROATATE_ANTI_CLOACK1 == direction || GameConfig::eKeys_LeftPlayer::ROATATE_ANTI_CLOACK2 == direction)
		{
			if (indexCenter != BLOCK_INDEX_CENTER)
			{
				RotateUntiClock(shape[indexCenter].getX(), shape[indexCenter].getY());
				timesOfRotation--;
			}
		}
		else
			noRotate = true;


		break;
	}
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
	{
		GameConfig::eKeys_RightPlayer direction = (GameConfig::eKeys_RightPlayer)keypressed;

		if (GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1 == direction || GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE2 == direction)
		{
			if (indexCenter != BLOCK_INDEX_CENTER)
			{
				RotateClock(shape[indexCenter].getX(), shape[indexCenter].getY());
				timesOfRotation++;
			}
		}
		else if (GameConfig::eKeys_RightPlayer::ROATATE_ANTI_CLOACK1 == direction || GameConfig::eKeys_RightPlayer::ROATATE_ANTI_CLOACK2 == direction)
		{
			if (indexCenter != BLOCK_INDEX_CENTER)
			{
				RotateUntiClock(shape[indexCenter].getX(), shape[indexCenter].getY());
				timesOfRotation--;
			}
		}
		else
			noRotate = true;

		break;
	}

	default:
		break;
	}

	if (noRotate)
	{
		shape[0].move(keypressed, indexPlayer);
		shape[1].move(keypressed, indexPlayer);
		shape[2].move(keypressed, indexPlayer);
		shape[3].move(keypressed, indexPlayer);
	}

	shape[0].setColor(this->backgroundcolor);
	shape[1].setColor(this->backgroundcolor);
	shape[2].setColor(this->backgroundcolor);
	shape[3].setColor(this->backgroundcolor);


}

/*This function rotates the tetromino clockwise.*/
void Tetromino::RotateClock(int centerX, int centerY)
{
	for (int i = 0; i < 4; i++)
	{
		int newX = centerX - centerY + shape[i].getY();
		int newY = centerY + centerX - shape[i].getX();
		shape[i].init(newX, newY);
	}

}

/*This function rotates the tetromino counterclockwise.*/
void Tetromino::RotateUntiClock(int centerX, int centerY)
{
	for (int i = 0; i < 4; i++)
	{
		int newX = centerX + centerY - shape[i].getY();
		int newY = centerY - centerX + shape[i].getX();
		shape[i].init(newX, newY);
	}

}

/*This function initializes the tetromino's shape and background color based on a random type and builds a boom in a 5% chances.*/
void Tetromino::buildShape()
{
	int probBomb = rand() % 100 + 1;

	if (probBomb <= 5)
		this->type = GameConfig::TetrisShapes::BOMB;
	else
		this->type = (GameConfig::TetrisShapes)(rand() % 7 + 1);


	switch (this->type)
	{
	case GameConfig::TetrisShapes::STRAIGHT:
	{
		shape[0].init(6, 1);
		shape[1].init(6, 2);
		shape[2].init(6, 3);
		shape[3].init(6, 4);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[1];

		indexCenter = 3;

	}
	break;
	case GameConfig::TetrisShapes::BLOCK:
	{
		shape[0].init(7, 1);
		shape[1].init(6, 1);
		shape[2].init(7, 2);
		shape[3].init(6, 2);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[2];

		indexCenter = -1;

	}
	break;
	case GameConfig::TetrisShapes::T_SHAPE:
	{
		shape[0].init(5, 1);
		shape[1].init(6, 1);
		shape[2].init(7, 1);
		shape[3].init(6, 2);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[3];

		indexCenter = 1;
	}
	break;
	case GameConfig::TetrisShapes::L_SHAPE:
	{
		shape[0].init(6, 1);
		shape[1].init(6, 2);
		shape[2].init(6, 3);
		shape[3].init(7, 3);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[4];

		indexCenter = 1;
	}
	break;
	case GameConfig::TetrisShapes::REV_L_SHAPE:
	{
		shape[0].init(6, 1);
		shape[1].init(6, 2);
		shape[2].init(6, 3);
		shape[3].init(5, 3);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[5];

		indexCenter = 1;

	}
	break;
	case GameConfig::TetrisShapes::LEFT_ZIG_ZAG:
	{
		shape[0].init(5, 1);
		shape[1].init(6, 1);
		shape[2].init(6, 2);
		shape[3].init(7, 2);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[6];

		indexCenter = 1;

	}
	break;
	case GameConfig::TetrisShapes::RIGHT_ZIG_ZAG:
	{
		shape[0].init(6, 1);
		shape[1].init(7, 1);
		shape[2].init(5, 2);
		shape[3].init(6, 2);

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[7];

		indexCenter = 0;
	}
	break;
	case GameConfig::TetrisShapes::BOMB:
		shape[0].init(6, 1);
		shape[1].init(6, 1);
		shape[2].init(6, 1);
		shape[3].init(6, 1);

		indexCenter = -1;

		if (this->backgroundcolor != GameConfig::COLORS[0])
			this->backgroundcolor = GameConfig::COLORS[8]; //7

	default:
		break;
	}

	shape[0].setColor(this->backgroundcolor);
	shape[1].setColor(this->backgroundcolor);
	shape[2].setColor(this->backgroundcolor);
	shape[3].setColor(this->backgroundcolor);


}

/*This function prints the shape of the tetromino on the game board*/
void Tetromino::printShape(const GameConfig::PlayerIndex indexPlayer)
{
	for (int i = 0; i < 4; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->backgroundcolor);

		switch (indexPlayer)
		{
		case GameConfig::PlayerIndex::LEFT_PLAYER:
			gotoxy(shape[i].getX() + GameConfig::PLAYER1_MIN_X - 1, shape[i].getY() + GameConfig::MIN_Y - 1);
			break;
		case GameConfig::PlayerIndex::RIGHT_PLAYER:
			gotoxy(shape[i].getX() + GameConfig::PLAYER2_MIN_X - 1, shape[i].getY() + GameConfig::MIN_Y - 1);
			break;
		default:
			break;
		}

		if (type == GameConfig::TetrisShapes::BOMB)
			cout << '!';
		else
			cout <<'*';

	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);

}
