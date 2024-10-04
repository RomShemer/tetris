#include "tetrisGame.h"
#include "gameConfig.h"
#include "general.h"
#include "board.h"
#include <iostream>
#include <Windows.h> // for Sleep and colors
#include <conio.h>
using namespace std;

#define NO_MOVE 0



void tetrisGame::runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer, bool isNewGame)
{

	if (isNewGame)
	{
		Board board;
		shape.buildShape();
		board.setShape(shape);
		board.addShapeToBoard(shape.getShapeArr());
	}
	else if (board.isValidMove(keypressed, indexPlayer))
	{
		shape.move(keypressed, indexPlayer);
		board.removeShapeFromBoard();
		board.setShape(shape);
		board.addShapeToBoard(shape.getShapeArr());
	}
	else if (board.isShapeStoped())
	{
		board.updateBoardIfNeeded();
		shape.buildShape();
		board.setShape(shape);
		board.addShapeToBoard(shape.getShapeArr());
	}
	else
	{
		shape.move(NO_MOVE,indexPlayer);
		board.removeShapeFromBoard();
		board.setShape(shape);
		board.addShapeToBoard(shape.getShapeArr());
	}

	Sleep(100);

	board.printBoard(indexPlayer);

}



