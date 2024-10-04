#include "gameConfig.h"

#include <Windows.h>


const int GameConfig::COLORS[] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, 176, 224, 95, 23, 48,BACKGROUND_INTENSITY | BACKGROUND_GREEN ,BACKGROUND_RED,110 };


const int GameConfig::COLORSHeadline[] = { FOREGROUND_BLUE | FOREGROUND_GREEN,FOREGROUND_BLUE | FOREGROUND_RED,FOREGROUND_BLUE,FOREGROUND_GREEN ,FOREGROUND_RED | FOREGROUND_GREEN, FOREGROUND_RED, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE };
const int GameConfig::NUM_OF_COLORS = sizeof(COLORS) / sizeof(int);

const int GameConfig::RandomMoveLeftPlayer[] = { (int)'a', (int)'d',(int)'s', (int)'w'}; // 0= moves down
const int GameConfig::RandomMoveRightPlayer[] = { (int)'j', (int)'l',(int)'k', (int)'i'}; // 0= moves down

const int GameConfig::NUM_OF_RANDOM_MOVES = sizeof(RandomMoveLeftPlayer) / sizeof(int);

