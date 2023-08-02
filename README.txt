OOP 2 - Ex04 - STL & Algorithms SFML 6 Color
-------------------
Name: David Zaydenberg
-------------------
Summary:

Recreate 6 color game in SFML using STL and it's algorithms and
implementing a generic data structure(Graph).
In this game you have a board with colors and shapes. You play
agains a computer on 3 difficulties. You choose a color to capture
in turns.

-------------------
Design:

Main creates a Controller class which controlls the loop of the game.
Controller has a loop that checks games state and respectedly enter the 
required function(like Menu or Play). It holds window class
member(for creating sf::RenderWindow), gamestate(Menu, Gameplay, Win, Lost, Exit),
GameBoard, MainMenu and Opponent members. Mainmenu is another function that shows
the menu when entering the game and after exiting the game, and it shows all 3
difficulties and lets us choose one or just exit the game.
Opponent is a unique_ptr variable of Opponent base class for 3 derived different
difficulty classes like Random, greedy and Global greedy ai's. each of them
uses different algorithms to select a color.
Controller as we said listens for input from the mouse and sends the mouse pos
into gameboard to handle the click. Aswell with the opponent when it's opponents
turn he chooses the color and controller sends the color to gameboard to take care
of taking over the boards tiles.
Gameboard create the generic Graph which is specifecly for this game is templated
for a Hexagon node type. All changes, traverse on the graph is happening in 
GameBoard. GameBoard draws the board, GameBoard has Ui which draws the ui over the
board. When we go back to the menu from the game, the board resets(function) so next
time when we enter a new game the board is ready to be played.
Ui as mentioned has all the ui(buttons and text - data). Buttons when taken are not
clickable. Ui shows also, percentage of captured tiles for the player and computer.
Graph class is out datastructure which holds all the nodes(tiles of hexagons).
For out specific needs I implemented a vector of templated nodes.
The graph is very generic so there are not specific traits. It has iterators implemented
in a different file. Iterator and ConstIterator that will help manage the graph.


-------------------
Files:

main.cpp - Sets random seed, creates a Controller and runs the game

Controller.cpp/h - Runs the main loop for different game states like menu and play.
In play, controlls the game flow and listening to mouse click event.

MainMenu.cpp/h - Draws the menu and holds all the sprites and buttons for the menu.

Window.cpp/h - Create a window and returns an sf::RenderWindow.

Config.h - Has all the consts relevant for the program(descriptions in file).

Color.cpp/h - Color managing class. has a colorcomparator struct for std::map
and a getRandomColor that returns a random color from 6 choices

Opponent.h/cpp - Base class for different difficulty derived classes and has 
a pure virtual makeMove function that gets GameBoard&.

RandomOpponent.cpp/h - Opponent chooses a random color for 6 choices

GreedyOpponent.cpp/h - Traverses over all of it's occupied nodes and checks only
for the current nodes neighbors, and counts the amount of occurence of specific
colors which are not taken by anyone and returns the most common color.

GlobalGreedyOpponnet.cpp/h - Traverses over all of it's occupied nodes by using
DFS techniques - goes over neighbors and neighbors of neighbors and more. and counts
the colors found that are not occupied by anyone and returns the most common color

GameBoard.cpp/h - Creates the board we play on and holds the Graph class
(generic templated data structure). Draws the board and lets the Ui class draw
ui objects. All operations over the graph are operated in this class(DFS/Traverse).

Graph.h - Generic graph uses templated nodes. has a Node struct as well and Controlled
by Iterators(normal and const)

Node.h - Struct for the graph that holds Nodes. Node has a templated member for the
member node, and a vector of neighbors(pointers).

Iterator.h - Iterator and ConstIterator classes are implemented for the generic Graph

Ui.cpp/h - Ui has all ui objects and draws them, controlls the occupied buttons and
percentage of capured amount of tiles by each player.

TextureManager/SoundManager.cpp/h - A singeltone classes which loads files from the
resources folder and holds Textures/SoundBuffer to return a const & when needed by
accessing the singeltone instance function.

Hexagon.cpp/h - The node type which we use. the hexagon is created with sf::CircleShape
by selecting 6 points and has occupied member and basic functions 

-------------------
DataStructure:
Generic Templated Graph(Class) that holds templated nodes(struct).
For out specific needs, I implemented for the graph, std::vector<Node<NodeType>>
to be the data structure that holds the nodes.
It has Iterator and ConstIterator implemented to secure the encapsulation.
The Node struct has the NodeType member (for out needs it's the Hexagon class)
visit boolian for when traversing DFS/BFS or other algorithms and a vector of
Nodes which are it's neighbors(pointers).

-------------------
Algorithms: 

Assigning neighbors - for each node first we add all 4 common neighbors that
are possible for each node to have if the current node meets the place(check the borders).
for other 4 unique neighbors we check depending on the row(even/odd), because hexagon
is a shape that that makes the shapes move to the side each row. algorithm is pretty straight
forward. (check it out in the gameboard).

Greedy opponent is straight forward, by going over all of it's occupied nodes
and for each node check only their neighbors if they are free and the color is not occupied
aswell and counts the colors amount, and in the end returns the most common color that
were saved in an std::map<sf::Color, int>.

GlobalGreedy Opponent uses real DFS algorithm which for each node that he owns, traverses
over it's neighbors, for each neighbor save the current color and goes for his neighbors and
continues for more and more neighbors of neighbors as long as the saved first color is the same
and the tile is not occupied, else we return. for every successful(not retuned) node we
added +1 for the count and set visit. At the end after returning and not finding anymore
we return the most common color to let the gameboard capture it for him.

colorBoard function which the player and AI uses to capture the color which is sent
through the arguments is iterating over the graph and for every node which is occupied
by the opponent or the player depending on the turn, and the node is not visited yet and 
the color is not the same already as the one we color with, we set the color of the node
and go into the captureConnectedNodes recursive function, which there we go to the 
neighbors of neighbors and capture all the colors that are connected to the chosen color.
This is also uses DFS algorithm.

-------------------
Bugs: None
-------------------
Notes: 

3 parts of implementing the game:

1) Data structure: I chose a Generic graph which holds templated nodes
which it's type is the shape that can be changed for futre use of the graph.
the graph is very native for this kind of game, because we have shapes that are
touching each other and need to act as neighbors which imidiatly reminds us of
a graph. each node has a vector of *nodes. The graph has Iterator and ConstIterator
classes to be able to operate over the graph without disrupting the encapsulation, 
and making the class kind of abstract and the inner implementation be hidden.

2) Logic implementation: The controller controlls the main loop for
the MainMenu, or the game(GameState). The GameBoard conrolls the Graph and draws it.
Ui controlls ui and draws UI. Window class provides the sf::renderwindow for the
controller to pass to the different classes for drawing.
Most importent functions that happens over the Graph are in the GameBoard.
Opponent base class is also in the Controller. Controller listens for click
and sends it for handling in the GameBoard and after that lets the opponent make
a move and gets a color and sends to the GameBoard to handle the coloring of the board.

3) Graphical implementation: Controller sends the sf::RenderWindow to the GameBoard
to draw the board. board in the same function sends the renderwindow to the UI class
to draw UI objects. The menu is drawn in the MainMenu function by the MainMenu class.

* To change the board size, inside the config.h file there's a const size_t BOARD_SIZE
  which tell you that the board is BOARD_SIZE * BOARD_SIZE.

-------------------