#include "point.h"
#include "gameConfig.h"
#include "general.h"

#include <iostream>
#include <Windows.h> // for Sleep and colors
using namespace std;

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/


void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
	this->diff_x = 0;
	this->diff_y = 1;

}

/*This function returns the x-coordinate of the Point.*/
int Point::getX()const
{
	return x;
}


/*This function returns the y-coordinate of the Point.*/
int Point::getY()const
{
	return y;
}


/*This function draws a character at the Point's coordinates on the console, considering the player index.*/
void Point::draw(char ch, const GameConfig::PlayerIndex indexPlayer)const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->backgroundcolor);

	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		gotoxy(x + GameConfig::PLAYER1_MIN_X - 1, y + GameConfig::MIN_Y - 1);
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		gotoxy(x + GameConfig::PLAYER2_MIN_X - 1, y + GameConfig::MIN_Y - 1);
		break;
	default:
		break;
	}

	cout << ch;
}


/*This function returns the background color of the Point.*/
int Point::getColor()const
{
	return backgroundcolor;
}


/*This function sets the background color of the Point.*/
void Point::setColor(int backcolor)
{
	this->backgroundcolor = backcolor;
}


/*This function moves the Point based on the key pressed and player index, and sets isDrop to true if a drop action is performed.*/
void Point::move(const int keypressed, const GameConfig::PlayerIndex indexPlayer)
{
	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:

		moveKeysLeftPlayer((GameConfig::eKeys_LeftPlayer)keypressed);
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:

		moveKeysRightPlayer((GameConfig::eKeys_RightPlayer)keypressed);
		break;
	default:
		break;
	}



}


/*This function moves the Point for the left player based on the left player's key pressed, updating isDrop accordingly.*/
void Point::moveKeysLeftPlayer(GameConfig::eKeys_LeftPlayer key)
{
	diff_x = 0;
	diff_y = 1;

	switch (key)
	{
	case GameConfig::eKeys_LeftPlayer::LEFT1:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys_LeftPlayer::LEFT2:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys_LeftPlayer::RIGHT1:
		diff_x = 1;
		diff_y = 0;
		break;
	case GameConfig::eKeys_LeftPlayer::RIGHT2:
		diff_x = 1;
		diff_y = 0;
		break;
	}


	x += diff_x;
	y += diff_y;


}


/*This function moves the Point for the left player based on the right player's key pressed, updating isDrop accordingly.*/
void Point::moveKeysRightPlayer(GameConfig::eKeys_RightPlayer key)
{
	diff_x = 0;
	diff_y = 1;

	switch (key)
	{
	case GameConfig::eKeys_RightPlayer::LEFT1:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys_RightPlayer::LEFT2:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys_RightPlayer::RIGHT1:
		diff_x = 1;
		diff_y = 0;
		break;
	case GameConfig::eKeys_RightPlayer::RIGHT2:
		diff_x = 1;
		diff_y = 0;
		break;
	}



	x += diff_x;
	y += diff_y;


}

