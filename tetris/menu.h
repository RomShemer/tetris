#ifndef __MENU_H
#define __MENU_H

#include "gameConfig.h"


/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class Menu
{

public:

	void printTetrisLogo() const;
	GameConfig::eKeys_MenuOptions printMenu() const;
	void printKeys() const;
	void printWithColorsOrNot(bool& withColors) const;
	GameConfig::eKeys_MenuOptions Menu_WithExitGame() const;
	GameConfig::eKeys_ComputerLevel printComputerLevelOptions(GameConfig::PlayerIndex indexPlayer) const;


};


#endif // !__MENU_H


