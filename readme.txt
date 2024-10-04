
Overview
This project implements a console-based Tetris game for two players, with support for additional features such as bombs, AI opponents, and color modes.

Features
Exercise 1: Basic Tetris Game
Two Players: Each player controls their own board (18x12 squares).

Controls: Players use specific keys to move, rotate, and drop the falling shapes.

Game End: The game ends when one player’s board reaches the top. The other player wins.

Menu Options:

Start a new game
Continue a paused game (if a game is paused)
View instructions and keys
Exit

Bonus Features:
Optional colors (toggle via menu).
Optional score tracking (used in case of a tie).

Exercise 2: Additional Features
Bombs: A bomb block has a 5% chance to appear. When it lands, it clears a 4x4 square radius around it.
AI Opponent: You can play against a computer with 3 difficulty levels: Best, Good, Novice.

New Menu Options:
Start a new game - Human vs. Human
Start a new game - Human vs. Computer
Start a new game - Computer vs. Computer
Continue paused game
View instructions and keys
Exit

System Requirements
Operating System: Windows
Development Environment: Visual Studio 2019 or later (e.g., VS 2021)
Console Screen Size: 80x25
Standard C++ Libraries

Controls

Left Player (A):
Move Left: a or A
Move Right: d or D
Rotate Clockwise: s or S
Rotate Counterclockwise: w or W
Drop: x or X

Right Player (B):
Move Left: j or J
Move Right: l or L
Rotate Clockwise: k or K
Rotate Counterclockwise: i or I
Drop: m or M

Pausing the Game:
Press ESC to pause the game and return to the main menu.

Additional Notes
The game uses gotoxy for positioning text on the console and _kbhit and _getch for non-blocking input.
For colors, SetConsoleTextAttribute is used (if the option is enabled).
No compiled binaries are included in the repository.
