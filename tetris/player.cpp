#include "player.h"
#include "general.h"
#include "gameConfig.h"
#include "tetromino.h"
#include "board.h"

#include <iostream>
#include <Windows.h> // for Sleep and colors
#include <conio.h>

using namespace std;

#define NO_MOVE 0

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/


/*This function Sets the player index (LEFT_PLAYER or RIGHT_PLAYER).*/
void Player::setIndexPlayer(GameConfig::PlayerIndex index)
{
	this->indexPlayer = index;

}

/*This function sets the game status to indicate whether it's a new game.*/
void Player::setGameStatus(bool isNewGame)
{
	this->isNewGame = isNewGame;

}


/*This function sets the color status to determine if color is used in the game.*/
void Player::setColorStatus(bool colorStatus)
{
	this->is_with_color = colorStatus;
}


/*This function returns the game status.*/
bool Player::getIsGameOver() const
{
	return GameOver;
}

/*This function return if the game was set with colors or not.*/
bool Player::getColorStatus() const
{
	return is_with_color;

}


/*This function returns if it is a new game*/
bool Player::getisNewGame()const
{
	return isNewGame;
}


/*This function returns the index of the player*/
GameConfig::PlayerIndex Player::getIndexPlayer() const
{
	return indexPlayer;
}

/*This function executes the player's actions based on the type of the player-human or computer.*/
void Player::run(int keypressed, GameConfig::PlayerIndex indexPlayer)
{

	if (isNewGame)
	{
		board.resetBoard();
		shape.SetColor(is_with_color);
		createShape();

		isNewGame = false;

	}
	else
		runPlayer(keypressed, indexPlayer);

}


/*This funcntion checks if the game is over based on the current board state and tetromino type.*/
void Player::isGameOver()
{
	int minY = 4;
	int maxY = 0;

	const Point* const ArrShape = shape.getShapeArr();

	for (int i = 0; i < 4; i++)
	{
		if (ArrShape[i].getY() < minY)
			minY = ArrShape[i].getY();
	}

	if (minY == 1)
		GameOver = true;

}

/*This function print the ending message of the loosing player*/
void Player::printEndingMessage()
{
	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		gotoxy(25, GameConfig::MIN_Y - 4);
		cout << "There is not enough place in Left player board :(";
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		gotoxy(25, GameConfig::MIN_Y - 4);
		cout << "There is not enough place in Right player board :(";
		break;
	default:
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	Sleep(400);
}



