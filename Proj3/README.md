## Connect-N Game
This project utilizes the fundamentals of C++ to create a variation of Connect-4 that can be played with any scaffold size and connect size. 
The game can be played against another human player, an 'easy' computer, or a 'hard' computer. 

### How to play: 
Since the source code is fully in C++, the game will be generated within the main file by utilizing the classes created. 
The Player file contains three types of Player classes: "SmartPlayer", "BadPlayer", and "HumanPlayer". You can generate a game by selecting any combination of the three options (even SmartPlayer against SmartPlayer where you can watch them play) and creating C++ objects with them. The only argument needed to be given is a name. 

For example, to create a SmartPlayer: </br>
SmartPlayer sp("Leo");

Then following the format of the Game class, create an object for this too. The arguments are: columns, rows, number of tokens to connect, player 1, and player 2, respectively. 

For example, to create a Game: </br>
Game game1(6,6,4,sp,sp2);

Now to play the game use the method "play" on the Game object we created. 

game1.play();

Now just compile the file and the game will run in the console. 

### More about the implementation: 
The project is built upon object-oriented programing where class objects create the premise of the game. 
The human player simply takes two player class objects which will take turns to play the game. 
The 'easy' computer takes a simple algorithm of locating first open position to make move. 
The 'hard' computer uses the minimax algorithm implemented with recursion to make move. 
Due to the scaling of the minimax algorithm, scaffolds of too large size may not work well with the 'hard' computer. 
