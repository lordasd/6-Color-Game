# 6 Color Game - Readme

## Overview

**Developer:** David Zaydenberg  
**Description:**  
This is a recreation of the **6 Color Game** using **SFML** and **C++ STL** with an implementation of a generic graph data structure. The game features a board with colors and shapes, where players take turns capturing tiles by selecting colors. Players can challenge the computer at three difficulty levels: *Random*, *Greedy*, and *Global Greedy*.  

## Features

- **Graph-Based Game Board:** A generic graph data structure (templated for hexagonal nodes) powers the game mechanics.
- **Dynamic Difficulty:** Opponent AI with increasing complexity:
  - **Random AI:** Selects random colors.
  - **Greedy AI:** Chooses the most common color among its immediate neighbors.
  - **Global Greedy AI:** Uses DFS to find the most dominant color across multiple levels of neighboring nodes.
- **Interactive UI:** 
  - Displays player and computer tile capture percentages.
  - Buttons and options to choose difficulty or exit the game.
- **Resettable Board:** Automatically resets when a new game starts.

---

## Architecture

### **Main Components**

1. **Main.cpp:**
   - Initializes the game with a `Controller` instance.
   - Sets the random seed for consistent random behavior.
   - Runs the main game loop.

2. **Controller Class:**
   - Manages game states (*Menu, Gameplay, Win, Lost, Exit*).
   - Handles input events and game flow.
   - Delegates actions to the `GameBoard` and `Opponent` components.

3. **GameBoard Class:**
   - Creates and manages the **Graph** of hexagonal nodes.
   - Executes operations like capturing tiles and traversing the graph.
   - Manages the board's UI overlay (e.g., buttons, score display).
   - Resets the board for new games.

4. **Opponent AI Classes:**
   - **Base Class:** Defines a pure virtual `makeMove` function.
   - **RandomOpponent:** Randomly selects a color.
   - **GreedyOpponent:** Chooses the most frequent neighbor color.
   - **GlobalGreedyOpponent:** Uses DFS to evaluate deeper neighbor connections.

5. **UI Components:**
   - Renders buttons, text, and score overlays.
   - Ensures buttons are unclickable after selection.

6. **Graph Class:**
   - A generic templated graph structure.
   - Includes a `Node` structure representing individual tiles.
   - Supports iterators for graph traversal (implemented in a separate file).

### **Other Components**

- **MainMenu:** Renders the main menu and manages difficulty selection or game exit.
- **Window:** Creates and provides an `sf::RenderWindow` instance.
- **Color Manager:** Provides random color selection and manages color comparison (e.g., for maps).

---

## Files and Descriptions

| **File**            | **Description**                                                                 |
|----------------------|---------------------------------------------------------------------------------|
| `main.cpp`          | Initializes the game and runs the main loop.                                   |
| `Controller.cpp/h`  | Manages game states, user inputs, and game flow.                               |
| `MainMenu.cpp/h`    | Handles rendering and interaction for the main menu.                          |
| `Window.cpp/h`      | Provides a windowing system using `sf::RenderWindow`.                         |
| `Config.h`          | Stores constant values for the game (e.g., configurations and descriptions).  |
| `Color.cpp/h`       | Manages game colors and provides random color selection.                      |
| `Opponent.h/cpp`    | Base class for AI opponents with pure virtual `makeMove` method.              |
| `RandomOpponent.cpp/h`| Implements random AI logic.                                                   |
| `GreedyOpponent.cpp/h`| Implements greedy AI logic based on immediate neighbors.                      |
| `GlobalGreedyOpponent.cpp/h` | Implements advanced AI using DFS-based evaluation.                     |
| `GameBoard.cpp/h`   | Creates the game board and handles graph operations.                          |
| `Graph.h`           | Implements a generic graph with templated nodes and iterators.               |

---

## How to Play

1. Launch the game.
2. Choose a difficulty level from the main menu (*Random, Greedy, Global Greedy*).
3. Play by selecting a color to capture tiles. The computer will take turns based on its AI logic.
4. The game ends when all tiles are captured. The player with the most tiles wins.

---

## Build Instructions

1. **Install Dependencies:**
   - **SFML Library:** Ensure SFML is installed and configured on your system.
   - **C++ Compiler:** Use a compiler supporting C++17 or newer.
2. **Compile the Game:**
   - Use your preferred build system or IDE.
   - Include all `.cpp` files and link against the SFML library.
3. **Run the Executable:**
   - Start the game and enjoy!

---

## Future Enhancements

- Add multiplayer mode for human vs. human gameplay.
- Expand AI with more sophisticated algorithms.
- Introduce custom board sizes and shapes for varied gameplay.

---

Enjoy playing **6 Color Game**! 🎮
