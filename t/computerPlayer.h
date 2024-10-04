#ifndef __COMPUTERPLAYER_H
#define __COMPUTERPLAYER_H

#define MOVE_SCORE 48
#include "gameConfig.h"
#include "tetromino.h"
#include "board.h"
#include "player.h"

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class ComputerPlayer : public Player
{
	int MovesScore[MOVE_SCORE];
	int Colcounter=0;
	int col;
	int numRotate=0;
	GameConfig::eKeys_ComputerLevel gameLevel;
	bool isTimeForRandomMove = false;
	int countRotationsInARow = 0;

public:

	virtual void runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer) override;
	void CreateMovesScoreArr();
	bool CheckIfShapeCanGoToCol(int col, Board& board, Tetromino& shape)const;
	void updateMovesScore(int col, int numRotate, Board& board, Tetromino& shape, int Tscore);
	void FindBestMove();
	void GoToColAndPrint(GameConfig::PlayerIndex indexPlayer);
	void createShape() override;
	void setGameLevel(GameConfig::eKeys_ComputerLevel level);
	void ChecksAndMakesnotBestMove();
	void makeRandomMove(bool noRotate);
	void printTypeOfPlayer() override;

};


#endif 