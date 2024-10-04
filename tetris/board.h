#ifndef __BOARD_H
#define __BOARD_H

#include "point.h"
#include "gameConfig.h"
#include "tetromino.h"

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class Board
{
	Point pBoard[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	Tetromino shape;
	int minRow = 18;


public:

	void setShape(Tetromino& shape);
	bool isShapeStoped();
	bool isValidMove(const int keypressed, const GameConfig::PlayerIndex indexPlayer);
	bool IsValidMoveLeftPlayer(const GameConfig::eKeys_LeftPlayer direction);
	bool IsValidMoveRightPlayer(const GameConfig::eKeys_RightPlayer direction);
	bool IsValidMoveByDirection(int diff_x, int diff_y, const Point* const ArrShape);
	bool IsValidTurnClock(int centerX, int centerY, const Point* const ArrShape);
	bool IsValidTurnUntiClock(int centerX, int centerY, const Point* const ArrShape);
	bool isCoordBelongToCurrShape(int Ind_x, int Ind_y, const Point* const ArrShape);
	void addShapeToBoard(const Point* ArrShape, int& score);
	void UpdateScore(const Point* const ArrShape, int& score);
	void updateBoardIfNeeded(int& score);
	void bombAllAround(int& score);
	bool isFloating(int col, int row, int color);
	void updateBoardAfterBomb();
	bool isLineFull(int lineNum)const;
	void removeLine(int lineNum);
	void printBoard(GameConfig::PlayerIndex playerIndex, int score)const;

	int getMinRow()const;


	void resetBoard();
};

#endif 


