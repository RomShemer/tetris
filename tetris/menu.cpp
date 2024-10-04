#include "menu.h"
#include "gameConfig.h"
#include "general.h"
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;


/*
Rom Shemer ID:206662587
Elizabeth Ashurov ID:209449321
*/


// this function prints the game logo 
void Menu::printTetrisLogo()const
{
    gotoxy(20, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "########  #######    ########   ############       ##     ############ \n";
    gotoxy(20, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[1]);
    cout << "   ##     ##            ##      ##        ##       ##     ##         \n";
    gotoxy(20, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[2]);
    cout << "   ##     ##            ##      ##       ##        ##        ##      \n";
    gotoxy(20, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[3]);
    cout << "   ##     ## ## ##      ##      #########          ##           ##   \n";
    gotoxy(20, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "   ##     ##            ##      ##      ##         ##             ##  \n";
    gotoxy(20, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "   ##     ##            ##      ##        ##       ##               ##\n";
    gotoxy(20, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[5]);
    cout << "   ##     #######       ##     #####        ##     ##     #############\n\n\n\n";


}

// this function prints the game menu
GameConfig::eKeys_MenuOptions Menu::printMenu()const
{
    int number = 0;

    system("cls");
    gotoxy(30, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "Menu\n";
    gotoxy(30, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(1) Start a new game - Human Vs Human\n";
    gotoxy(30, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(2) Start a new game - Human Vs Computer\n";
    gotoxy(30, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(3) Start a new game - Computer Vs Computer\n";
    gotoxy(30, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(8) Present instructions and keys\n";
    gotoxy(30, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(9) EXIT \n\n";

    gotoxy(30, 16);

    cin >> number;
    system("cls");

    return (GameConfig::eKeys_MenuOptions)number;
}


//this function prints the keys table of the players
void Menu::printKeys()const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    gotoxy(22, 8);
    cout << "Keys:";
    gotoxy(22, 9);
    cout << "___________________________________________________________";
    gotoxy(22, 10);
    cout << "|                         |  Left Player |  Right Player  |";
    gotoxy(22, 11);
    cout << "|_________________________|_____________ |________________|";
    gotoxy(22, 12);
    cout << "| LEFT                    | a or A       | j or J         |";
    gotoxy(22, 15);
    cout << "|_________________________|_____________ |________________|";
    gotoxy(22, 13);
    cout << "| RIGHT                   | d or D       | l or L         |";
    gotoxy(22, 14);
    cout << "|_________________________|______________|________________|";
    gotoxy(22, 15);
    cout << "| ROTATE clockwise        | s or S       | k or K         |";
    gotoxy(22, 16);
    cout << "|_________________________|______________|________________|";
    gotoxy(22, 17);
    cout << "| ROTATE counterclockwise | w or W       | i or I         |";
    gotoxy(22, 18);
    cout << "|_________________________|______________|________________|";
    gotoxy(22, 19);
    cout << "| DROP                    | x or X       | m or M         |";
    gotoxy(22, 20);
    cout << "|_________________________|______________|________________|\n";


    Sleep(200);
}

//this function gets from the player his choise according to the colors (with ir without)
void Menu::printWithColorsOrNot(bool& withColors)const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);

    int num = 0;
    gotoxy(22, 10);
    cout << "Press (4) if you want your game to run without colors and (2) otherwise" << endl;
    gotoxy(22, 11);

    cin >> num;
    system("cls");

    if (num == 4)
        withColors = false;

}

/* This function prints the options of levels of the computer player*/
GameConfig::eKeys_ComputerLevel Menu::printComputerLevelOptions(GameConfig::PlayerIndex indexPlayer)const
{
    char c;

    system("cls");
    gotoxy(30, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    switch (indexPlayer)
    {
    case GameConfig::PlayerIndex::LEFT_PLAYER:
        cout << "Choose the level of the Left computer player\n";
        break;
    case GameConfig::PlayerIndex::RIGHT_PLAYER:
        cout << "Choose the level of the Right computer player\n";
        break;
    default:
        break;
    }
    gotoxy(30, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(a) BEST\n";
    gotoxy(30, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(b) GOOD\n";
    gotoxy(30, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[0]);
    cout << "(c) NOVICE\n";
    gotoxy(30, 14);

    cin >> c;
    system("cls");

    return (GameConfig::eKeys_ComputerLevel)c;

}

//this function prints the menu after one of the player chose to paused the game (with option to continue), and gets the players chooises
GameConfig::eKeys_MenuOptions Menu::Menu_WithExitGame()const
{
    int number = 0;

    system("cls");
    gotoxy(30, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "Menu\n";
    gotoxy(30, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "(1) Start a new game - Human Vs Human\n";
    gotoxy(30, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "(2) Start a new game - Human Vs Computer\n";
    gotoxy(30, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "(3) Start a new game - Computer Vs Computer\n";
    gotoxy(30, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "(4) Continue a paused game\n";
    gotoxy(30, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "(8) Present instructions and keys\n";
    gotoxy(30, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORSHeadline[4]);
    cout << "(9) EXIT \n\n";

    gotoxy(30, 17);

    cin >> number;
    system("cls");

    return (GameConfig::eKeys_MenuOptions)number;
}
