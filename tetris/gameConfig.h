#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#include <windows.h> 

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class GameConfig
{

public:
	//This class holds constants and overall variables for the whole game
	enum class eKeys_LeftPlayer { LEFT1 = 'a', LEFT2 = 'A', RIGHT1 = 'd', RIGHT2 = 'D', ROATATE_CLOACKWISE1 = 's', ROATATE_CLOACKWISE2 = 'S', ROATATE_ANTI_CLOACK1 = 'w', ROATATE_ANTI_CLOACK2 = 'W', DROP1 = 'x', DROP2 = 'X' };
	enum class eKeys_RightPlayer { LEFT1 = 'j', LEFT2 = 'J', RIGHT1 = 'l', RIGHT2 = 'L', ROATATE_CLOACKWISE1 = 'k', ROATATE_CLOACKWISE2 = 'K', ROATATE_ANTI_CLOACK1 = 'i', ROATATE_ANTI_CLOACK2 = 'I', DROP1 = 'm', DROP2 = 'M' };
	enum class eKeys_MenuOptions { HUMAN_VS_HUMAN = 1, HUMAN_VS_COMPUTER, COMPUTER_VS_COMPUTER, CONTINUE_GAME = 4, GAME_WITH_COLORS = 3, PRESENT_INSTRUCTIONS_KEYS = 8, EXIT = 9, ESC = 27 };
	enum class eKeys_ComputerLevel{BEST='a', GOOD, NOVICE};
	static const int RandomMoveLeftPlayer[];
	static const int RandomMoveRightPlayer[];
	static const int NUM_OF_RANDOM_MOVES;

	enum class PlayerType { HUMAN = 1, COMPUTER };
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int PLAYER1_MIN_X = 20;
	static constexpr int PLAYER2_MIN_X = 70;
	static constexpr int MIN_Y = 6;

	static const int COLORS[];
	static const int COLORSHeadline[];
	static const int NUM_OF_COLORS;
	const int ORIGINAL_CONSOLE_COLOR = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	enum class TetrisShapes { STRAIGHT = 1, BLOCK, T_SHAPE, L_SHAPE, REV_L_SHAPE, LEFT_ZIG_ZAG, RIGHT_ZIG_ZAG, BOMB};
	enum class PlayerIndex { NON = 0, LEFT_PLAYER = 1, RIGHT_PLAYER };



};


#endif 



