#ifndef __HUMANPLAYER_H
#define __HUMANPLAYER_H

#include "player.h"

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class HumanPlayer : public Player
{
public:
	void runPlayer(int keypressed, GameConfig::PlayerIndex indexPlayer) override;
	void createShape()override;
	bool CheckIfDropAndDoDrop(int keypressed, GameConfig::PlayerIndex indexPlayer);
	void printTypeOfPlayer()override;

};


#endif