#ifndef __TETRIS_GAME_H
#define __TETRIS_GAME_H

#include "tetromino.h"
#include "board.h" 

class tetrisGame
{
	Tetromino shape;
	Board board;

public:

	void runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer, bool isNewGame);



};

#endif 

