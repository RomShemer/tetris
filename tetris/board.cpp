#include "board.h"
#include <windows.h>
#include <iostream>
#include "general.h"
#include <iomanip>

using namespace std;

#define EMPTY -1
#define RIGHT 1
#define LEFT -1
#define NO_MOVE 0
#define BLOCK_INDEX_CENTER -1
#define DOWN 1


/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/


/*This function sets the current shape of the board*/
void Board::setShape(Tetromino& shape)
{
	this->shape = shape;
}


/*This function returns the minimum row of the current shape*/
int Board::getMinRow() const
{
	return minRow;
}


/*This function checks if the current shape has stopped (reached the bottom or another block).*/
bool Board::isShapeStoped()
{
	int row, col;
	const Point* ArrShape = shape.getShapeArr();
	GameConfig::TetrisShapes type = shape.getType();
	int minY = 19;

	for (int i = 0; i <= 3; i++)
	{
		row = ArrShape[i].getY() - 1;
		col = ArrShape[i].getX() - 1;

		if (row < minY)
			minY = row;

		if (row == GameConfig::GAME_HEIGHT - 1 || (pBoard[col][row + 1].getY() != EMPTY && !isCoordBelongToCurrShape(col + 1, row + 2, ArrShape)))
		{
			if (minY < minRow)
				minRow = minY;


			return true;
		}

	}



	return false;
}


/*This function checks if the move indicated by the key pressed is valid for the given player.
The function calls the functions: -IsValidMoveLeftPlayer
								  -IsValidMoveRightPlayer
*/
bool Board::isValidMove(const int keypressed, const GameConfig::PlayerIndex indexPlayer)
{

	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		return IsValidMoveLeftPlayer((GameConfig::eKeys_LeftPlayer)keypressed);
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		return IsValidMoveRightPlayer((GameConfig::eKeys_RightPlayer)keypressed);
		break;
	default:
		break;
	}
}


/*This function checks if the move indicated by the key pressed is valid for the left player
The function calls the functions: -IsValidMoveByDirection
								  -IsValidTurnClock
								  -IsValidTurnUntiClock
.*/
bool Board::IsValidMoveLeftPlayer(const GameConfig::eKeys_LeftPlayer direction)
{

	const Point* ArrShape = shape.getShapeArr();
	int diff_x, diff_y;

	switch (direction)
	{
	case GameConfig::eKeys_LeftPlayer::LEFT1:
		diff_x = LEFT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::LEFT2:
		diff_x = LEFT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::RIGHT1:
		diff_x = RIGHT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::RIGHT2:
		diff_x = RIGHT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE2:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::ROATATE_ANTI_CLOACK1:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnUntiClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::ROATATE_ANTI_CLOACK2:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnUntiClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_LeftPlayer::DROP1:

		diff_x = NO_MOVE;
		diff_y = DOWN;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);
		break;
	case GameConfig::eKeys_LeftPlayer::DROP2:
		diff_x = NO_MOVE;
		diff_y = DOWN;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);
		break;
	default:
		diff_x = 0;
		diff_y = 1;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);
		break;
	}

}


/*This function checks if the move indicated by the key pressed is valid for the right player.
The function calls the functions: -IsValidMoveByDirection
								  -IsValidTurnClock
								  -IsValidTurnUntiClock
*/
bool Board::IsValidMoveRightPlayer(const GameConfig::eKeys_RightPlayer direction)
{

	const Point* ArrShape = shape.getShapeArr();
	int diff_x, diff_y;

	switch (direction)
	{
	case GameConfig::eKeys_RightPlayer::LEFT1:
		diff_x = LEFT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::LEFT2:
		diff_x = LEFT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::RIGHT1:
		diff_x = RIGHT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::RIGHT2:
		diff_x = RIGHT;
		diff_y = NO_MOVE;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE2:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::ROATATE_ANTI_CLOACK1:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnUntiClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::ROATATE_ANTI_CLOACK2:

		if (shape.getIndexCenter() == BLOCK_INDEX_CENTER)
			return false;

		diff_x = ArrShape[shape.getIndexCenter()].getX();
		diff_y = ArrShape[shape.getIndexCenter()].getY();
		return IsValidTurnUntiClock(diff_x, diff_y, ArrShape);

		break;
	case GameConfig::eKeys_RightPlayer::DROP1:

		diff_x = NO_MOVE;
		diff_y = DOWN;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);
		break;
	case GameConfig::eKeys_RightPlayer::DROP2:

		diff_x = NO_MOVE;
		diff_y = DOWN;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);
		break;
	default:
		diff_x = 0;
		diff_y = 1;
		return IsValidMoveByDirection(diff_x, diff_y, ArrShape);
		break;
	}

}


/*This function checks if the move indicated by the keys: left, right, drop (and no key- going down), that has been pressed is valid.*/
bool Board::IsValidMoveByDirection(int diff_x, int diff_y, const Point* const ArrShape)
{
	int row, col;

	for (int i = 0; i < 4; i++)
	{
		row = ArrShape[i].getY() - 1 + diff_y;
		col = ArrShape[i].getX() - 1 + diff_x;

		if (row < 0 || row >= GameConfig::GAME_HEIGHT || col < 0 || col >= GameConfig::GAME_WIDTH)
			return false;

		else if (pBoard[col][row].getY() != EMPTY && isCoordBelongToCurrShape(col + 1, row + 1, ArrShape) == false)
		{
			return false;

		}

	}

	return true;

}


/*This function checks if the move indicated by the key turn clockwise that has been pressed is valid.*/
bool Board::IsValidTurnClock(int centerX, int centerY, const Point* const ArrShape)
{

	for (int i = 0; i < 4; i++)
	{
		int newX = centerX - centerY + ArrShape[i].getY() - 1;
		int newY = centerY + centerX - ArrShape[i].getX() - 1;

		if (newY < 0 || newY >= GameConfig::GAME_HEIGHT || newX < 0 || newX >= GameConfig::GAME_WIDTH)
			return false;

		if (pBoard[newX][newY].getY() != EMPTY && isCoordBelongToCurrShape(newX + 1, newY + 1, ArrShape) == false)
			return false;

	}

	return true;
}


/*This function checks if the move indicated by the key turn untiClockwise that has been pressed is valid.*/
bool Board::IsValidTurnUntiClock(int centerX, int centerY, const Point* const ArrShape)
{

	for (int i = 0; i < 4; i++)
	{
		int newX = centerX + centerY - ArrShape[i].getY() - 1;
		int newY = centerY - centerX + ArrShape[i].getX() - 1;

		if (newY < 0 || newY >= GameConfig::GAME_HEIGHT || newX < 0 || newX >= GameConfig::GAME_WIDTH)
			return false;


		if (pBoard[newX][newY].getY() != EMPTY && isCoordBelongToCurrShape(newX + 1, newY + 1, ArrShape) == false)
			return false;

	}
	return true;

}


/*This function checks if given coordinates belong to the current shape.*/
bool Board::isCoordBelongToCurrShape(int Ind_x, int Ind_y, const Point* const ArrShape)
{
	bool belong = false;

	for (int i = 0; i < 4; i++)
	{
		if (ArrShape[i].getX() == Ind_x && ArrShape[i].getY() == Ind_y)
			belong = true;
	}

	return belong;
}


/*This function adds the current shape to the board and call the function UpdateScore.*/
void Board::addShapeToBoard(const Point* ArrShape, int& score)
{


	for (int i = 0; i < 4; i++)
	{
		int row = ArrShape[i].getY() - 1;
		int col = ArrShape[i].getX() - 1;
		pBoard[col][row].init(col + 1, row + 1);
		pBoard[col][row].setColor(shape.getColor());


	}

	UpdateScore(ArrShape, score);

}

/*This function updates the score based on the current state of the game board and the position of the tetromino shape*/
void Board::UpdateScore(const Point* const ArrShape, int& score)
{
	int maxRow = 0;
	int col, row;

	for (int i = 0; i < 4; i++)
	{
		row = ArrShape[i].getY() - 1;
		col = ArrShape[i].getX() - 1;


		if (col + 1 < GameConfig::GAME_WIDTH && pBoard[col + 1][row].getY() != EMPTY && isCoordBelongToCurrShape(col+2, row + 1, ArrShape) == false)
			score += 2;
		else if (col - 1 >= 0 && pBoard[col - 1][row].getY() != EMPTY && isCoordBelongToCurrShape(col, row + 1, ArrShape) == false)
			score += 2;
		else if (col == 11)
			score += 20;
		else if (col == 0)
			score += 20;


		if (row + 1 < GameConfig::GAME_HEIGHT && pBoard[col][row + 1].getY() != EMPTY && isCoordBelongToCurrShape(col + 1, row + 2, ArrShape) == false)
			score += 25 ; 
		else if (row == 17)
			score += 50;

		if (row > maxRow)
			maxRow = row;
	}


		score = score + (maxRow * 50);

		if (maxRow <= 8)
			score = score - 1500;

		for (int i = 0; i < 4; i++)
		{
			row = ArrShape[i].getY() - 1;
			col = ArrShape[i].getX() - 1;

			if (row + 1 < GameConfig::GAME_HEIGHT && isCoordBelongToCurrShape(col + 1, row + 2, ArrShape) == false)
			{
				for (row = maxRow + 1; row < GameConfig::GAME_HEIGHT; row++)
				{
					if (pBoard[col][row].getY() == EMPTY)
						score = score -400; 

				}


			}

		}
	
}

/*This function updates the game board after placing a tetromino shape. 
If the shape is not a bomb, it checks for full rows and removes them and updates the score 
If it is a bomb it calss the function bombAllAround*/
void Board::updateBoardIfNeeded(int& score)
{
	if (shape.getType() == GameConfig::TetrisShapes::BOMB)
		bombAllAround(score);
	else
	{
		for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
		{
			if (isLineFull(i))
			{
				removeLine(i);
				if(i<=GameConfig::GAME_HEIGHT-6)
				   score += 1500;
				else if(i <= GameConfig::GAME_HEIGHT -3)
					score += 2000;
				else
					score += 1000;

			}
		}
	}

}

/*This function triggers a bomb explosion effect in a distance of a 4 squares and updates the score*/
void Board::bombAllAround(int& score)
{
	int indexX = (shape.getShapeArr())[0].getX() - 1;
	int indexY = (shape.getShapeArr())[0].getY() - 1;


	for (int col = indexX - 4; col <= indexX + 4; col++)
	{
		for (int row = indexY - 4; row <= indexY + 4; row++)
		{
			if ((col >= 0 && col < GameConfig::GAME_WIDTH) && (row >= 0 && row < GameConfig::GAME_HEIGHT))
			{
				pBoard[col][row].init(EMPTY, EMPTY);
				pBoard[col][row].setColor(GameConfig::COLORS[0]);
				score += 2;

			}
		}
	}

	updateBoardAfterBomb();
}

/*This function updates the board after a bomb explosion, shifting down any cells that have empty space below them*/
void Board::updateBoardAfterBomb()
{
	int color;

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		for (int row = GameConfig::GAME_HEIGHT - 1; row >= 0; row--)
		{

			if (row + 1 < GameConfig::GAME_HEIGHT && (pBoard[col][row].getY() != EMPTY && pBoard[col][row + 1].getY() == EMPTY))
			{
				for (int i = row; i < GameConfig::GAME_HEIGHT - 1; i++)
				{
					color = pBoard[col][row].getColor();

					if (pBoard[col][row + 1].getY() == EMPTY)
					{
						pBoard[col][row + 1].init(col + 1, row + 2);
						pBoard[col][row + 1].setColor(color);
						pBoard[col][row].init(EMPTY, EMPTY);
						pBoard[col][row].setColor(GameConfig::COLORS[0]);
					}
				}

			}

		}
	}
}

/*This function checks if a given line is full.*/
bool Board::isLineFull(int lineNum) const
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		if (pBoard[i][lineNum].getY() == EMPTY)
			return false;
	}
	return true;
}

/*This function removes a full line.*/
void Board::removeLine(int lineNum)
{
	int x, y, color;

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		for (int row = lineNum; row > 0; row--)
		{

			color = pBoard[col][row - 1].getColor();

			if (pBoard[col][row - 1].getY() != EMPTY)
			{
				pBoard[col][row].init(col + 1, row + 1);
				pBoard[col][row].setColor(color);
			}
			else
			{
				pBoard[col][row].init(EMPTY, EMPTY);
				pBoard[col][row].setColor(GameConfig::COLORS[0]);

			}

			pBoard[col][row - 1].init(EMPTY, EMPTY);
			pBoard[col][row - 1].setColor(GameConfig::COLORS[0]);

		}
	}


}

/*This function prints the current state of the board.*/
void Board::printBoard(GameConfig::PlayerIndex playerIndex, int score) const
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			if (pBoard[i][j].getY() == EMPTY)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);

				switch (playerIndex)
				{
				case GameConfig::PlayerIndex::LEFT_PLAYER:

					gotoxy(i + GameConfig::PLAYER1_MIN_X, j + GameConfig::MIN_Y);
					break;
				case GameConfig::PlayerIndex::RIGHT_PLAYER:

					gotoxy(i + GameConfig::PLAYER2_MIN_X, j + GameConfig::MIN_Y);
					break;
				default:
					break;
				}
				cout << ' ';
			}
			else
			{
				pBoard[i][j].draw(shape.getShapeChar(), playerIndex);

			}

		}
	}


	//print score
	switch (playerIndex)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:

		gotoxy(GameConfig::PLAYER1_MIN_X-1, 20 + GameConfig::MIN_Y);
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:

		gotoxy(GameConfig::PLAYER2_MIN_X-1, 20 + GameConfig::MIN_Y);
		break;
	default:
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	cout << "The Score: " << std::setw(3)<< std::setfill('0') << score;

}


/*This function resets the board to its initial state.*/
void Board::resetBoard()
{
	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		for (int row = 0; row < GameConfig::GAME_HEIGHT; row++)
		{
			pBoard[col][row].init(EMPTY, EMPTY);
			pBoard[col][row].setColor(GameConfig::COLORS[0]);
		}
	}
}


