#include "twoPlayersGame.h"

#include <conio.h> // for kbhit+getch
#include <iostream>
#include <iomanip>
#include <Windows.h> // for Sleep and colors
using namespace std;

#include "gameConfig.h"
#include "general.h"
#include "tetrisGame.h"
#include "menu.h"
#include "player.h"
#include "computerPlayer.h"


#define RETURN_BACK 1
#define GAME_OVER -1

/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/

/*This function displays the game menu and initializes players (LeftPlayer and RightPlayer).
  Based on the menu choice, either starts a new game, presents instructions, or exits.*/
void TwoPlayersGame::startGame()
{
	bool isWithColor = true;
	int num = 0;
	GameConfig::eKeys_ComputerLevel computerLevel;

	print_Logo();
	GameConfig::eKeys_MenuOptions player_choice = GameMenu.printMenu();
	

	switch (player_choice)
	{
	case GameConfig::eKeys_MenuOptions::HUMAN_VS_HUMAN:

		isNewGame = true;
		LeftPlayer = new HumanPlayer();
		RightPlayer = new HumanPlayer();

		LeftPlayer->setIndexPlayer(GameConfig::PlayerIndex::LEFT_PLAYER);
		RightPlayer->setIndexPlayer(GameConfig::PlayerIndex::RIGHT_PLAYER);

		setForNewGame(isWithColor);

		break;
	case GameConfig::eKeys_MenuOptions::HUMAN_VS_COMPUTER:
		
		isNewGame = true;
		LeftPlayer = new HumanPlayer();
		RightPlayer = new ComputerPlayer();
		
		LeftPlayer->setIndexPlayer(GameConfig::PlayerIndex::LEFT_PLAYER);
		RightPlayer->setIndexPlayer(GameConfig::PlayerIndex::RIGHT_PLAYER);

		computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());

		while (!isValidChoiseGameLevel(computerLevel))
		{
			computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		}
		((ComputerPlayer*)RightPlayer)->setGameLevel(computerLevel);

		setForNewGame(isWithColor);

		break;
	case GameConfig::eKeys_MenuOptions::COMPUTER_VS_COMPUTER:

		isNewGame = true;
		LeftPlayer = new ComputerPlayer();
		RightPlayer = new ComputerPlayer();

		LeftPlayer->setIndexPlayer(GameConfig::PlayerIndex::LEFT_PLAYER);
		RightPlayer->setIndexPlayer(GameConfig::PlayerIndex::RIGHT_PLAYER);

		computerLevel = GameMenu.printComputerLevelOptions(LeftPlayer->getIndexPlayer());
		while (!isValidChoiseGameLevel(computerLevel))
		{
			computerLevel = GameMenu.printComputerLevelOptions(LeftPlayer->getIndexPlayer());
		}
		((ComputerPlayer*)LeftPlayer)->setGameLevel(computerLevel);


		computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		while (!isValidChoiseGameLevel(computerLevel))
		{
			computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		}
		((ComputerPlayer*)RightPlayer)->setGameLevel(computerLevel);


		setForNewGame(isWithColor);

		break;

	case GameConfig::eKeys_MenuOptions::PRESENT_INSTRUCTIONS_KEYS:
		GameMenu.printKeys();
		gotoxy(22, 21);
		cout << "press 1 key to return to menu ";

		cin >> num;

		if (num == RETURN_BACK)
			player_choice = GameMenu.printMenu();
		break;

	case GameConfig::eKeys_MenuOptions::EXIT:

		delete LeftPlayer;
		delete RightPlayer;

		gotoxy(35, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
		cout << "           :( " << endl;
		gotoxy(40, 14);
		cout << "Hope you will return soon..." << endl;
		isGameEnded = true;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
		gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 20);
	default:
		break;
	}


	if (player_choice != GameConfig::eKeys_MenuOptions::EXIT && !isGameEnded)
	{
		Sleep(4000);
		system("cls");
		drawBorder();
		run_Game();
	}
	else  if(isPlayerChoiseIsNewGame(player_choice) && isGameEnded && isNewGame)
	{
		isGameEnded = false;
		startGame();
	}
	else if (player_choice == GameConfig::eKeys_MenuOptions::EXIT && isGameEnded)
	{
		gotoxy(40, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
		cout << "           :( " << endl;
		gotoxy(40, 14);
		cout << "Hope you will return soon..." << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
		gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 20);
	}
	else
	{

		gotoxy(45, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
		cout << "The Game ended";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
		gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 20);
	}

}

/*This function checks if the chosen computer level for the game is valid */
bool TwoPlayersGame::isValidChoiseGameLevel(GameConfig::eKeys_ComputerLevel computerLevel)
{
	if (computerLevel == GameConfig::eKeys_ComputerLevel::BEST || computerLevel == GameConfig::eKeys_ComputerLevel::GOOD ||computerLevel == GameConfig::eKeys_ComputerLevel::NOVICE)
         return true;
	else
	{
		gotoxy(40, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
		cout << "Invalid choise, please try again";
		Sleep(1500);
		return false;
	}
}

/*This function checks if the player's choice indicates starting a new game*/
bool TwoPlayersGame::isPlayerChoiseIsNewGame(GameConfig::eKeys_MenuOptions player_choice) const
{
	if (player_choice == GameConfig::eKeys_MenuOptions::HUMAN_VS_COMPUTER || player_choice == GameConfig::eKeys_MenuOptions::HUMAN_VS_HUMAN || player_choice == GameConfig::eKeys_MenuOptions::COMPUTER_VS_COMPUTER)
		return true;
	else
		return false;

}

/*This function prepares for a new game by setting up*/
void TwoPlayersGame::setForNewGame(bool isWithColor)
{
	GameMenu.printWithColorsOrNot(isWithColor);
	LeftPlayer->setGameStatus(isNewGame);
	RightPlayer->setGameStatus(isNewGame);

	LeftPlayer->setColorStatus(isWithColor);
	RightPlayer->setColorStatus(isWithColor);

	drawBorder();
	run_Game();
}

/*This function draws the game border, including separate sections for the left and right players.*/
void TwoPlayersGame::drawBorder()const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
	LeftPlayer->printTypeOfPlayer();

	for (int col = GameConfig::PLAYER1_MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::PLAYER1_MIN_X; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";

	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::PLAYER1_MIN_X - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::PLAYER1_MIN_X, row);
		cout << "|";
	}

	gotoxy(GameConfig::PLAYER1_MIN_X, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
	cout << "Left player";

	gotoxy(GameConfig::PLAYER1_MIN_X - 1, 20 + GameConfig::MIN_Y);
	cout << "The Score: " << std::setw(3) << std::setfill('0') <<0;

	RightPlayer->printTypeOfPlayer();

	for (int col = GameConfig::PLAYER2_MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::PLAYER2_MIN_X; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";

	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::PLAYER2_MIN_X - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::PLAYER2_MIN_X, row);
		cout << "|";
	}

	gotoxy(GameConfig::PLAYER2_MIN_X, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
	cout << "Right player";

	gotoxy(GameConfig::PLAYER2_MIN_X - 1, 20 + GameConfig::MIN_Y);
	cout << "The Score: " << std::setw(3) << std::setfill('0') << 0;
}

/*This function prints the Tetris logo and introduces a delay before clearing the screen.*/
void TwoPlayersGame::print_Logo()const
{
	GameMenu.printTetrisLogo();
	Sleep(4000);
}

/*This function runs the main game loop, handling player inputs and updating the game state.
  Checks for game over conditions for both players.*/
void TwoPlayersGame::run_Game()
{

	while (!isGameEnded)
	{
		int KeyPressed = 0;

		for (int i = 0; i < 10 && !isGameEnded; i++)
		{
			if (_kbhit())
			{
				KeyPressed = _getch();

				if (IsLeftPlayerKeyPressed(KeyPressed))
				{
					LeftPlayer->run(KeyPressed, GameConfig::PlayerIndex::LEFT_PLAYER);
					RightPlayer->run(0, GameConfig::PlayerIndex::RIGHT_PLAYER);

				}

				if (IsRightPlayerKeyPressed(KeyPressed))
				{
					LeftPlayer->run(0, GameConfig::PlayerIndex::LEFT_PLAYER);
					RightPlayer->run(KeyPressed, GameConfig::PlayerIndex::RIGHT_PLAYER);

				}

				if (KeyPressed == (int)GameConfig::eKeys_MenuOptions::ESC)
				{
					Sleep(2000);
					system("cls");
					PrintPaused();
					Sleep(4000);
					system("cls");
					ExitWasChosen();
					break;
				}
			}
			else
			{

				LeftPlayer->run(0, GameConfig::PlayerIndex::LEFT_PLAYER);
				RightPlayer->run(0, GameConfig::PlayerIndex::RIGHT_PLAYER);


			}



			if (LeftPlayer->getIsGameOver())
			{
				Sleep(1000);
				system("cls");
				printingWinner(GameConfig::PlayerIndex::RIGHT_PLAYER);

				delete LeftPlayer;
				delete RightPlayer;

				Sleep(2000);
				isGameEnded = true;
				system("cls");
				_kbhit();
				gotoxy(35,12);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
				cout << "Press any key to return to the menu";
				Sleep(4000);
				if (_kbhit())
				{
					KeyPressed = _getch();
					isNewGame = true;

				}
				else
				{
					isNewGame = false;
				}


			}
			else if (RightPlayer->getIsGameOver())
			{
				Sleep(1000);
				system("cls");
				printingWinner(GameConfig::PlayerIndex::LEFT_PLAYER);

				delete LeftPlayer;
				delete RightPlayer;

				Sleep(2000);
				isGameEnded = true;
				system("cls");
				_kbhit();
				gotoxy(35, 12);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
				cout << "Press any key to return to the menu";
				Sleep(4000);
				if (_kbhit())
				{
					KeyPressed = _getch();
					isNewGame = true;

				}
				else
				{
					isNewGame = false;
				}
			}



		}


	}
}

/*This function checks if the key pressed corresponds to a valid input for the left player.*/
bool TwoPlayersGame::IsLeftPlayerKeyPressed(int KeyPressed)const
{
	char ch = (char)KeyPressed;

	if (ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D' || ch == 's' || ch == 'S' || ch == 'w' || ch == 'W' || ch == 'x' || ch == 'X')
		return true;

}

/*This function checks if the key pressed corresponds to a valid input for the right player.*/
bool TwoPlayersGame::IsRightPlayerKeyPressed(int KeyPressed)const
{
	char ch = (char)KeyPressed;

	if (ch == 'j' || ch == 'J' || ch == 'l' || ch == 'L' || ch == 'k' || ch == 'K' || ch == 'i' || ch == 'I' || ch == 'm' || ch == 'M')
		return true;

}

/*This function handles the user's choice when selecting the exit option from the menu.
  Allows the user to start a new game, view instructions, continue the current game, or exit.*/
void TwoPlayersGame::ExitWasChosen()
{
	int num = 0;
	bool isWithColor = true;
	GameConfig::eKeys_ComputerLevel computerLevel;
	GameConfig::eKeys_MenuOptions player_choice = GameMenu.Menu_WithExitGame();

	switch (player_choice)
	{
	case GameConfig::eKeys_MenuOptions::HUMAN_VS_HUMAN:

		isNewGame = true;
		delete LeftPlayer;
		delete RightPlayer;

		LeftPlayer = new HumanPlayer();
		RightPlayer = new HumanPlayer();

		LeftPlayer->setIndexPlayer(GameConfig::PlayerIndex::LEFT_PLAYER);
		RightPlayer->setIndexPlayer(GameConfig::PlayerIndex::RIGHT_PLAYER);

		setForNewGame(isWithColor);

		break;
	case GameConfig::eKeys_MenuOptions::HUMAN_VS_COMPUTER:

		isNewGame = true;
		delete LeftPlayer;
		delete RightPlayer;

		LeftPlayer = new HumanPlayer();
		RightPlayer = new ComputerPlayer();

		LeftPlayer->setIndexPlayer(GameConfig::PlayerIndex::LEFT_PLAYER);
		RightPlayer->setIndexPlayer(GameConfig::PlayerIndex::RIGHT_PLAYER);

		computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		while (!isValidChoiseGameLevel(computerLevel))
		{
			computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		}

		((ComputerPlayer*)RightPlayer)->setGameLevel(computerLevel);

		setForNewGame(isWithColor);

		break;
	case GameConfig::eKeys_MenuOptions::COMPUTER_VS_COMPUTER:
		
		isNewGame = true;
		delete LeftPlayer;
		delete RightPlayer;

		LeftPlayer = new ComputerPlayer();
		RightPlayer = new ComputerPlayer();

		LeftPlayer->setIndexPlayer(GameConfig::PlayerIndex::LEFT_PLAYER);
		RightPlayer->setIndexPlayer(GameConfig::PlayerIndex::RIGHT_PLAYER);

		computerLevel = GameMenu.printComputerLevelOptions(LeftPlayer->getIndexPlayer());
		while (!isValidChoiseGameLevel(computerLevel))
		{
			computerLevel = GameMenu.printComputerLevelOptions(LeftPlayer->getIndexPlayer());
		}
		((ComputerPlayer*)LeftPlayer)->setGameLevel(computerLevel);


		computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		while (!isValidChoiseGameLevel(computerLevel))
		{
			computerLevel = GameMenu.printComputerLevelOptions(RightPlayer->getIndexPlayer());
		}
		((ComputerPlayer*)RightPlayer)->setGameLevel(computerLevel);


		setForNewGame(isWithColor);

		break;
	case GameConfig::eKeys_MenuOptions::PRESENT_INSTRUCTIONS_KEYS:
		GameMenu.printKeys();
		gotoxy(22, 21);
		cout << "press 1 key to return to menu ";

		cin >> num;

		if (num == RETURN_BACK)
			player_choice = GameMenu.Menu_WithExitGame();

		break;

	case GameConfig::eKeys_MenuOptions::CONTINUE_GAME:

		isNewGame = false;

		LeftPlayer->setGameStatus(isNewGame);
		RightPlayer->setGameStatus(isNewGame);


		drawBorder();
		run_Game();
		break;

	case GameConfig::eKeys_MenuOptions::EXIT:

		delete LeftPlayer;
		delete RightPlayer;

		gotoxy(45, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
		cout << "The Game ended";
		isGameEnded = true;
		isNewGame = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
		gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 20);
		break;

	default:
		break;
	}

	if (player_choice == GameConfig::eKeys_MenuOptions::EXIT)
	{
		gotoxy(40, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
		cout << "           :( " << endl;
		gotoxy(40, 14);
		cout << "Hope you will return soon..." << endl;
		isGameEnded = true;
		isNewGame = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
		gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 20);
	}

	if (player_choice != GameConfig::eKeys_MenuOptions::EXIT && !isGameEnded)
	{
		Sleep(4000);
		system("cls");
		drawBorder();
		run_Game();
	}



}


/*This function prints a message declaring the winner of the game based on the player index.*/
void TwoPlayersGame::printingWinner(GameConfig::PlayerIndex indexPlayer)const
{
	int color = 0;
	string text;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);


	switch (indexPlayer)
	{
	case GameConfig::PlayerIndex::LEFT_PLAYER:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		text = "Left player is the winner!!!";
		break;
	case GameConfig::PlayerIndex::RIGHT_PLAYER:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		text = "Right player is the winner!!!";
		break;
	default:
		break;
	}

	for (size_t i = 0; i < text.length(); ++i)
	{
		gotoxy(40 + i, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[color]);
		cout << text[i];

		if (color > 5)
			color = 0;
		else
			color++;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[6]);
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 6);
}


void TwoPlayersGame::PrintPaused()const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[2]);
	gotoxy(12, 10);
	cout << " ######   ####   ###   ###   #####     ######   ####   ##    ##  #######  #####  #######    ";
	gotoxy(12, 11);
	cout << " ##      ##  ##  ## # # ##   ##        ##  ##  #    #  ##    ##    ##     ##     ##    ##  ";
	gotoxy(12, 12);
	cout << " ## ###  ######  ##  #  ##   #####     #####   ######  ##    ##     ###   #####  ##     ##  ";
	gotoxy(12, 13);
	cout << " ##  #   ##  ##  ##     ##   ##        ##      ##  ##  ##    ##       ##  ##     ##    ##  ";
	gotoxy(12, 14);
	cout << " #####   ##  ##  ##     ##   #####     ##      ##  ##    ####   #######   #####  ######   ";


}
