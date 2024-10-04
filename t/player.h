#ifndef __PLAYER_H
#define __PLAYER_H

#include "gameConfig.h"
#include "tetromino.h"
#include "board.h"


#include <iostream>
using namespace std;

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class Player
{
	bool GameOver = false;
	bool is_with_color = true;
	bool isNewGame = true;

protected:
	Tetromino shape;
	Board board;
	GameConfig::PlayerIndex indexPlayer;
	int score = 0;

public:

	void setIndexPlayer(GameConfig::PlayerIndex index);
	void setGameStatus(bool isNewGame);
	void setColorStatus(bool colorStatus);
	bool getIsGameOver()const;
	bool getColorStatus()const;
	bool getisNewGame()const;
	GameConfig::PlayerIndex getIndexPlayer() const;
	virtual void createShape() = 0;
	void run(int keypressed, GameConfig::PlayerIndex indexPlayer);
	virtual void runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer) = 0;
	void isGameOver();
	void printEndingMessage();
	virtual void printTypeOfPlayer()=0;

	virtual ~Player() {}
};


#endif 

