#include <conio.h> // for kbhit+getch
#include <iostream>
#include <Windows.h> // for Sleep and colors
using namespace std;

#include "player.h"
#include "gameConfig.h";
#include "general.h"
#include "twoPlayersGame.h"
#include "tetrisGame.h"
#include <cstdlib>

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

void main()
{
	srand(time(nullptr));

	TwoPlayersGame game;
	game.startGame();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
	gotoxy(0,50);

}





