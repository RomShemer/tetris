#include "humanPlayer.h"
#include "general.h"
#include <iostream>
using namespace std;

#define NO_MOVE 0



/*This function executes the player's actions based on the key pressed and player index.*/
void HumanPlayer::runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer)
{
	bool Drop = false;


	Drop = CheckIfDropAndDoDrop(keypressed, indexPlayer);

	if (Drop)
	{
		isGameOver();

		if (getIsGameOver())
		{
			board.printBoard(indexPlayer, score);
			printEndingMessage();

		}
		else
		{
			createShape();
			shape.printShape(indexPlayer);
		}


	}
	else if (board.isValidMove(keypressed, indexPlayer) && !Drop)
	{
		board.printBoard(indexPlayer, score);
		shape.move(keypressed, indexPlayer, true);
		shape.printShape(indexPlayer);
		board.setShape(shape);


	}
	else if (board.isShapeStoped() && !Drop)
	{

		isGameOver();

		if (getIsGameOver())
		{
			board.printBoard(indexPlayer, score);
			printEndingMessage();

		}
		else
		{
			board.addShapeToBoard(shape.getShapeArr(), score);
			board.updateBoardIfNeeded(score);
			board.printBoard(indexPlayer, score);
			createShape();
    		shape.printShape(indexPlayer);
		}



	}
	else if (!Drop)
	{
		shape.move(NO_MOVE, indexPlayer, true);
		shape.printShape(indexPlayer);
		board.setShape(shape);
	}

	Sleep(200);

}


void HumanPlayer::createShape()
{
	shape.buildShape();
	board.setShape(shape);
}


bool HumanPlayer::CheckIfDropAndDoDrop(int keypressed, GameConfig::PlayerIndex indexPlayer)
{
	bool drop = false;

	if (indexPlayer == GameConfig::PlayerIndex::LEFT_PLAYER)
	{
		GameConfig::eKeys_LeftPlayer direction = (GameConfig::eKeys_LeftPlayer)keypressed;
		if (direction == GameConfig::eKeys_LeftPlayer::DROP1 || direction == GameConfig::eKeys_LeftPlayer::DROP2)
		{
			drop = true;
			while (board.isShapeStoped() == false)
			{
				board.printBoard(indexPlayer, score);
				shape.move(NO_MOVE, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				Sleep(50);
			}

		}
	}
	else
	{
		GameConfig::eKeys_RightPlayer direction = (GameConfig::eKeys_RightPlayer)keypressed;
		if (direction == GameConfig::eKeys_RightPlayer::DROP1 || direction == GameConfig::eKeys_RightPlayer::DROP2)
		{
			drop = true;
			while (board.isShapeStoped() == false)
			{
				board.printBoard(indexPlayer, score);
				shape.move(NO_MOVE, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				Sleep(50);
			}
		}

	}

	if (drop)
	{
		board.addShapeToBoard(shape.getShapeArr(), score);
		board.updateBoardIfNeeded(score);
		board.printBoard(indexPlayer, score);
	}

	return drop;

}

void HumanPlayer::printTypeOfPlayer()
{
	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		gotoxy(GameConfig::PLAYER1_MIN_X, GameConfig::MIN_Y - 3);
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		gotoxy(GameConfig::PLAYER2_MIN_X, GameConfig::MIN_Y - 3);
		break;
	default:
		break;
	}

	cout << "Human Player" << endl;

}


