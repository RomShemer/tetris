#ifndef __POINT_H
#define __POINT_H

#include "gameConfig.h"

class Point
{
	int x;
	int y;
	int diff_x;
	int diff_y;
	int backgroundcolor;

public:

	Point()
	{
		x = -1;
		y = -1;
		diff_x = 0;
		diff_x = 0;
		backgroundcolor = GameConfig::COLORS[0];

	}
	void init(int x, int y);
	int getX()const;
	int getY()const;
	int getColor()const;
	void draw(char c, const GameConfig::PlayerIndex indexPlayer)const;
	void setColor(int backcolor);

	void move(const int keypressed, const GameConfig::PlayerIndex indexPlayer);
	void moveKeysLeftPlayer(GameConfig::eKeys_LeftPlayer key);
	void moveKeysRightPlayer(GameConfig::eKeys_RightPlayer key);



};


#endif 