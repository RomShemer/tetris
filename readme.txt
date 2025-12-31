# 🎮 Two-Player Console Tetris (C++)

A classic **console-based Tetris game** written in **C++**, supporting **two players**, **AI opponents**, **bomb mechanics**, and **optional color modes**.  
Built as part of a structured programming exercise, with clean separation of game logic, input handling, and rendering.

---

## 📽️ Gameplay Demo

https://github.com/user-attachments/assets/12468237-2b19-4692-8bb9-8b999fdde212

---

## ✨ Features

### 🧩 Exercise 1 – Core Game
- **Two Players**  
  Each player controls their own board (**18x12** grid).

- **Independent Controls**  
  Each player has a dedicated key set for movement, rotation, and drop.

- **Win Condition**  
  The game ends when one player's board reaches the top.  
  The opponent is declared the winner.

- **Game Menu**
  - Start a new game
  - Continue a paused game
  - View instructions & controls
  - Exit

---

### 🎁 Bonus Features
- 🎨 **Optional Color Mode** (toggle from menu)
- 🧮 **Optional Score Tracking** (used to resolve ties)

---

### 🚀 Exercise 2 – Advanced Features
- 💣 **Bomb Blocks**
  - 5% chance to spawn
  - Clears a **4×4 area** upon landing

- 🤖 **AI Opponent**
  - Three difficulty levels:
    - **Best**
    - **Good**
    - **Novice**

- 🧭 **Extended Game Modes**
  - Human vs. Human
  - Human vs. Computer
  - Computer vs. Computer

---

## 🖥️ System Requirements

| Requirement | Details |
|------------|--------|
| Operating System | Windows |
| Compiler / IDE | Visual Studio 2019+ (recommended: VS 2021) |
| Console Size | 80 × 25 |
| Language | C++ |
| Libraries | Standard C++ + Windows Console API |

---
## 🎮 Controls

| Action | Left Player (A) | Right Player (B) |
|--------|-----------------|------------------|
| Move Left | **A** | **J** |
| Move Right | **D** | **L** |
| Rotate Clockwise | **S** | **K** |
| Rotate Counterclockwise | **W** | **I** |
| Drop | **X** | **M** |

---

### ⏸️ Pause Game
- Press **ESC** to pause and return to the main menu.

---

## 🛠️ Technical Notes
- Uses `gotoxy` for precise console rendering.
- Non-blocking input handled with `_kbhit()` and `_getch()`.
- Color support implemented via `SetConsoleTextAttribute`.
- No precompiled binaries included — build directly from source.

---

## 📌 Project Highlights
✔ Two-player real-time console gameplay  
✔ Modular and readable C++ code  
✔ AI logic with adjustable difficulty  
✔ Clean console UI with optional colors  
