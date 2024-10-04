#ifndef __TWOP_PLAYERS_GAME
#define __TWOP_PLAYERS_GAME


#include "menu.h"
#include "player.h"
#include "computerPlayer.h"
#include "humanPlayer.h"

class TwoPlayersGame
{
	Menu GameMenu;
	Player* LeftPlayer=nullptr;
	Player* RightPlayer=nullptr;
	bool isNewGame = true;
	bool isGameEnded = false;




public:

	void startGame();
	void setForNewGame(bool isWithColor);
	void drawBorder()const;
	void print_Logo()const;
	void run_Game();
	bool IsLeftPlayerKeyPressed(int KeyPressed)const;
	bool IsRightPlayerKeyPressed(int KeyPressed)const;
	void ExitWasChosen();
	void printingWinner(GameConfig::PlayerIndex indexPlayer)const;
	void PrintPaused()const;
	bool isPlayerChoiseIsNewGame(GameConfig::eKeys_MenuOptions player_choice) const;
	bool isValidChoiseGameLevel(GameConfig::eKeys_ComputerLevel computerLevel);


};







#endif // !1
