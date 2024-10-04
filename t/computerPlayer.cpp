#include "computerPlayer.h"
#include "general.h"
#include "gameConfig.h"
#include "tetromino.h"
#include "board.h"

#include <iostream>
#include <iomanip>
#include <Windows.h> // for Sleep and colors
#include <conio.h>
using namespace std;

#define NO_MOVE 0

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

/*This function sets the game level (BEST, GOOD, NOVICE) for the computer playe*/
void ComputerPlayer::setGameLevel(GameConfig::eKeys_ComputerLevel level)
{
	this->gameLevel = level;
}

/*This function executes the  computer player's actions based on the chosen level.*/
void ComputerPlayer::runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer)
{
	bool isBomb = false;

	const Point* ArrShape = shape.getShapeArr();

	if (!board.isShapeStoped())
	{
		if (shape.getType() == GameConfig::TetrisShapes::BOMB && (gameLevel == GameConfig::eKeys_ComputerLevel::NOVICE))
		{
			isBomb = true;
			isTimeForRandomMove = true;
		}

		if (!isTimeForRandomMove)
		{
			if (Colcounter > 0 || numRotate > 0)
				GoToColAndPrint(indexPlayer);
			else
			{
				shape.move(NO_MOVE, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
			}
		}
		else
			ChecksAndMakesnotBestMove();
	
	}
	else
	{

	      board.addShapeToBoard(shape.getShapeArr(), score);
	      board.updateBoardIfNeeded(score);
	      board.printBoard(indexPlayer, score);

		  isGameOver();
		  if (getIsGameOver())
		  {
			  // endOfGame
			  board.printBoard(indexPlayer, score);
			  printEndingMessage();
		  }
		  else
		  {
			  //createShape();
			  createShape();
			  shape.printShape(indexPlayer);

			  if (isTimeForRandomMove)
			  {
				  isTimeForRandomMove = false;
				  countRotationsInARow = 0;
			  }
			  if (isBomb)
				  isBomb = false;
		  }
	}


	Sleep(70);

	
}

/*This function checks and makes a move for the computer player, considering the game level.*/
void ComputerPlayer::ChecksAndMakesnotBestMove()
{
	int prob = 0;
	bool noRotate = false;

    if (gameLevel == GameConfig::eKeys_ComputerLevel::GOOD)
	{
		prob=rand() % 40 + 1;

		if (prob % 40 == 0 && prob > 0)
			isTimeForRandomMove = true;

		if (countRotationsInARow > 4)
			noRotate = true;

		makeRandomMove(noRotate);

		
	}
	else if (gameLevel == GameConfig::eKeys_ComputerLevel::NOVICE)
	{
		prob = rand() % 10 + 1;

		if (prob % 10 == 0 && prob > 0)
			isTimeForRandomMove = true;

		if (countRotationsInARow > 4)
			noRotate = true;

		makeRandomMove(noRotate);


	}
	

}

/*This function makes a random move for the computer player, considering the current game level.*/
void ComputerPlayer::makeRandomMove(bool noRotate)
{
	int randomMove=0;
	bool isLeftPlayer = false;
	bool isBomb = false;

	if (shape.getType() == GameConfig::TetrisShapes::BOMB)
		isBomb = true;

	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		if (isBomb)
			randomMove = (int)GameConfig::eKeys_LeftPlayer::LEFT1;
		else
		{
			if (noRotate)
				randomMove = (int)GameConfig::RandomMoveLeftPlayer[rand() % (GameConfig::NUM_OF_RANDOM_MOVES - 2)];
			else
				randomMove = (int)GameConfig::RandomMoveLeftPlayer[rand() % GameConfig::NUM_OF_RANDOM_MOVES];
		}
 
		isLeftPlayer = true;
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		if (isBomb)
			randomMove = (int)GameConfig::eKeys_RightPlayer::LEFT1;
		else
		{
			if (noRotate)
				randomMove = (int)GameConfig::RandomMoveRightPlayer[rand() % (GameConfig::NUM_OF_RANDOM_MOVES - 2)];
			else
				randomMove = (int)GameConfig::RandomMoveRightPlayer[rand() % GameConfig::NUM_OF_RANDOM_MOVES];
		}

		break;
	default:
		break;
	}

	if (isBomb && !board.isValidMove(randomMove, indexPlayer))
		randomMove = NO_MOVE;

	while (!board.isValidMove(randomMove, indexPlayer) && !isBomb)
	{
		switch (indexPlayer)
		{
		case GameConfig::PlayerIndex::LEFT_PLAYER:
			if (noRotate)
				randomMove = (int)GameConfig::RandomMoveLeftPlayer[rand() % (GameConfig::NUM_OF_RANDOM_MOVES - 2)];
			else
				randomMove = (int)GameConfig::RandomMoveLeftPlayer[rand() % GameConfig::NUM_OF_RANDOM_MOVES];
			break;
		case GameConfig::PlayerIndex::RIGHT_PLAYER:
			if (noRotate)
				randomMove = (int)GameConfig::RandomMoveRightPlayer[rand() % (GameConfig::NUM_OF_RANDOM_MOVES - 2)];
			else
				randomMove = (int)GameConfig::RandomMoveRightPlayer[rand() % GameConfig::NUM_OF_RANDOM_MOVES];
			break;
		}
	}


	//makes sure there is no too much rotations in a row in a random move
	if (isLeftPlayer && !isBomb)
	{
		if (((GameConfig::eKeys_LeftPlayer)randomMove == GameConfig::eKeys_LeftPlayer::ROATATE_ANTI_CLOACK1) || ((GameConfig::eKeys_LeftPlayer)randomMove == GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1))
			countRotationsInARow++;
		else
			countRotationsInARow = 0;
	}
	else if(!isBomb)
	{
		if (((GameConfig::eKeys_RightPlayer)randomMove == GameConfig::eKeys_RightPlayer::ROATATE_ANTI_CLOACK1) || ((GameConfig::eKeys_RightPlayer)randomMove == GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1))
			countRotationsInARow++;
		else
			countRotationsInARow = 0;
	}

	shape.move(randomMove, indexPlayer, true);
	shape.printShape(indexPlayer);
	board.setShape(shape);

}

/*This function creates a new shape for the computer player and calls the functions:
                                                                               -CreateMovesScoreArr
																			   -FindBestMove */
void ComputerPlayer::createShape()
{
	shape.buildShape();
	board.setShape(shape);
	shape.printShape(indexPlayer);
	CreateMovesScoreArr();
	FindBestMove();
}

/*This function moves the shape to a specific column and prints it.*/
void ComputerPlayer::GoToColAndPrint(GameConfig::PlayerIndex indexPlayer)
{
	if (indexPlayer == GameConfig::PlayerIndex::LEFT_PLAYER) //if left player
	{
		//Do rotate
		if (numRotate >= 1)
		{
			if (board.isValidMove((int)GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1, indexPlayer) == false) // for shapes like zigzag
			{
				shape.move(NO_MOVE, indexPlayer, true);
				board.setShape(shape);
				shape.printShape(indexPlayer);
			}

				shape.move((int)GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1, indexPlayer, true);
				board.setShape(shape);
				shape.printShape(indexPlayer);
				numRotate--;


		}
		else if (col <= 6)
		{
			if (board.isValidMove((int)GameConfig::eKeys_LeftPlayer::LEFT1, indexPlayer))
			{
				shape.move((int)GameConfig::eKeys_LeftPlayer::LEFT1, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				Colcounter--;

			}
			else
			{
				if (!board.isShapeStoped())
				{
					shape.move(NO_MOVE, indexPlayer, true);
					board.setShape(shape);
					shape.printShape(indexPlayer);
				}

			}

		}
		else
		{
			if (board.isValidMove((int)GameConfig::eKeys_LeftPlayer::RIGHT1, indexPlayer))
			{
				shape.move((int)GameConfig::eKeys_LeftPlayer::RIGHT1, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				Colcounter--;
			}
			else
			{
				if (!board.isShapeStoped())
				{
					shape.move(NO_MOVE, indexPlayer, true);
					board.setShape(shape);
					shape.printShape(indexPlayer);
				}


			}
		}


	}

	else // if right player
	{
		//Do rotate
		if (numRotate >= 1)
		{
			if (board.isValidMove((int)GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1, indexPlayer) == false) // for shapes like zigzag
			{
				shape.move(NO_MOVE, indexPlayer, true);
				board.setShape(shape);
				shape.printShape(indexPlayer);
			}

				shape.move((int)GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				numRotate--;



		}
		else if (col <= 6)
		{

			if (board.isValidMove((int)GameConfig::eKeys_RightPlayer::LEFT1, indexPlayer))
			{
				shape.move((int)GameConfig::eKeys_RightPlayer::LEFT1, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				Colcounter--;
			}
			else if (!board.isShapeStoped())
			{
				shape.move(NO_MOVE, indexPlayer, true);
				board.setShape(shape);
				shape.printShape(indexPlayer);
			}

		}
		else 
		{
			if (board.isValidMove((int)GameConfig::eKeys_RightPlayer::RIGHT1, indexPlayer))
			{
				shape.move((int)GameConfig::eKeys_RightPlayer::RIGHT1, indexPlayer, true);
				shape.printShape(indexPlayer);
				board.setShape(shape);
				Colcounter--;
			}
			else if (!board.isShapeStoped())
			{
				shape.move(NO_MOVE, indexPlayer, true);
				board.setShape(shape);
				shape.printShape(indexPlayer);
			}

		}

	}

		

	//Sleep(200);
}

/*This function creates an array to store the scores for each possible move*/
void ComputerPlayer::CreateMovesScoreArr()
{
	bool rotate = true;
	int tempScore;

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		tempScore = score;
		Tetromino shapeTemp = shape;
		Board tempBoard = board;
		tempBoard.setShape(shapeTemp);

		// before rotate
		if (CheckIfShapeCanGoToCol(col, tempBoard, shapeTemp))
			updateMovesScore(col, 0, tempBoard, shapeTemp, tempScore);
		else MovesScore[4 * col] = -1;



		// for rotates
		for (int numRotate = 1; numRotate < 4; numRotate++)
		{
			shapeTemp = shape;
			shapeTemp.move(NO_MOVE, indexPlayer, false);
			tempBoard.setShape(shapeTemp);
			tempScore = score;
			tempBoard = board;

			if (indexPlayer == GameConfig::PlayerIndex::LEFT_PLAYER)
			{
				for (int i = 0; i < numRotate; i++)
				{
					if (tempBoard.isValidMove((int)GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1, indexPlayer) == false) // for shapes like zigzag
					{
						shapeTemp.move(NO_MOVE, indexPlayer, false);
						tempBoard.setShape(shapeTemp);
					}
					shapeTemp.move((int)GameConfig::eKeys_LeftPlayer::ROATATE_CLOACKWISE1, indexPlayer, false);
					tempBoard.setShape(shapeTemp);
				}
			}
			else
			{
				for (int i = 0; i < numRotate; i++)
				{
					if (tempBoard.isValidMove((int)GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1, indexPlayer) == false)
					{
						shapeTemp.move(NO_MOVE, indexPlayer, false);
						tempBoard.setShape(shapeTemp);
					}
					shapeTemp.move((int)GameConfig::eKeys_RightPlayer::ROATATE_CLOACKWISE1, indexPlayer, false);
					tempBoard.setShape(shapeTemp);
				}
			}


			if (CheckIfShapeCanGoToCol(col, tempBoard, shapeTemp) && rotate)
				updateMovesScore(col, numRotate, tempBoard, shapeTemp, tempScore);
			else
				MovesScore[(4 * col) + numRotate] = -1;

		}
	}
}

/*This function checks if the shape can move to a specific column*/
bool ComputerPlayer::CheckIfShapeCanGoToCol(int col, Board& board, Tetromino& shape)const
{
	bool res = true;

	if (indexPlayer == GameConfig::PlayerIndex::LEFT_PLAYER) //if left player
	{
		if (col <= 6)
		{
			for (int i = 0; i < 6 - col && res; i++)
			{
				res = board.isValidMove((int)GameConfig::eKeys_LeftPlayer::LEFT1, indexPlayer);
				if (res)
				{
					shape.move((int)GameConfig::eKeys_LeftPlayer::LEFT1, indexPlayer, false);
					board.setShape(shape);
				}
			}
		}
		else
		{
			for (int i = 0; i < col - 6 && res; i++)
			{
				res = board.isValidMove((int)GameConfig::eKeys_LeftPlayer::RIGHT1, indexPlayer);
				if (res)
				{
					shape.move((int)GameConfig::eKeys_LeftPlayer::RIGHT1, indexPlayer, false);
					board.setShape(shape);
				}
			}

		}
	}
	else // if right player
	{
		if (col <= 6)
		{
			for (int i = 0; i < 6 - col && res; i++)
			{
				res = board.isValidMove((int)GameConfig::eKeys_RightPlayer::LEFT1, indexPlayer);
				if (res)
				{
					shape.move((int)GameConfig::eKeys_RightPlayer::LEFT1, indexPlayer, false);
					board.setShape(shape);
				}
			}
		}
		else
		{
			for (int i = 0; i < col - 6 && res; i++)
			{
				res = board.isValidMove((int)GameConfig::eKeys_RightPlayer::RIGHT1, indexPlayer);
				if (res)
				{
					shape.move((int)GameConfig::eKeys_RightPlayer::RIGHT1, indexPlayer, false);
					board.setShape(shape);
				}
			}

		}
	}

	return res;

}

/*This function updates the scores for each possible move and save it in the compmuter data member-MovesScore*/
void ComputerPlayer::updateMovesScore(int col, int numRotate, Board& board, Tetromino& shape, int Tscore)
{
	// goes down until shapeStopped
	bool countinue = true;

	while (countinue)
	{
		if (board.isShapeStoped())
		{
			countinue = false;
			board.addShapeToBoard(shape.getShapeArr(), Tscore);
			board.updateBoardIfNeeded(Tscore);
		}

		else
		{
			shape.move(NO_MOVE, indexPlayer, false);
			board.setShape(shape);
		}
	}

	MovesScore[(4 * col) + numRotate] = Tscore;

}

/*This function finds the best move based on the scores of each possible move*/
void ComputerPlayer::FindBestMove()
{
	int maxScore = -1;
	int bestMove = 0;
	int counter = 0;

	for (int i = 0; i < MOVE_SCORE; i++)
	{

		if (MovesScore[i] == maxScore)
		{
			if (counter % 2 == 0)
			{
				maxScore = MovesScore[i];
				bestMove = i;
				counter++;
			}
		}
		else if (MovesScore[i] > maxScore)
		{
			maxScore = MovesScore[i];
			bestMove = i;
		}
	}

	col = bestMove / 4;
	numRotate = bestMove % 4;

	if (col <= 6)
		Colcounter = 6 - col;
	else
		Colcounter = col - 6;
}

/*This function prints the type of player (Computer Player) and the game level.*/
void ComputerPlayer::printTypeOfPlayer()
{
	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		gotoxy(GameConfig::PLAYER1_MIN_X-1, GameConfig::MIN_Y - 3);
		cout << "Computer Player";
		gotoxy(GameConfig::PLAYER1_MIN_X - 3, GameConfig::MIN_Y - 2);
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		gotoxy(GameConfig::PLAYER2_MIN_X-1, GameConfig::MIN_Y - 3);
		cout << "Computer Player";
		gotoxy(GameConfig::PLAYER2_MIN_X - 3, GameConfig::MIN_Y - 2);
		break;
	default:
		break;
	}

	switch (gameLevel)
	{
	case GameConfig::eKeys_ComputerLevel::BEST:
			cout << setw(17) << setfill(' ') << std::right << "Game level: BEST";
		break;
	case GameConfig::eKeys_ComputerLevel::GOOD:
		    cout << setw(17) << setfill(' ') << std::right << "Game level: GOOD";
		break;
	case GameConfig::eKeys_ComputerLevel::NOVICE:
		cout << "Game level: NOVICE" << endl;

		break;
	default:
		break;
	}

}





