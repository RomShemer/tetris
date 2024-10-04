#ifndef __SHAPE_H
#define __SHAPE_H

#include "point.h"

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

class Tetromino
{
	char ch = '*';
	int backgroundcolor;
	Point shape[4];
	GameConfig::TetrisShapes type;
	int indexCenter;
	int timesOfRotation = 0;

public:

	const Point* getShapeArr()const;
	int getColor()const;
	char getShapeChar()const;
	GameConfig::TetrisShapes getType()const;
	int getIndexCenter()const;
	int getTimesOfRotations()const;
	void SetColor(bool IsWithColor);

	void RotateClock(int centerX, int centerY);
	void RotateUntiClock(int centerX, int centerY);
	void buildShape();

	void move(const int keypressed, const GameConfig::PlayerIndex indexPlayer, bool RealMove);
	void printShape(const GameConfig::PlayerIndex indexPlayer); //new
};

#endif 

