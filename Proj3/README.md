Connect-N Game
This project utilizes the fundamentals of C++ to create a variation of Connect-4 that can be played with any scaffold size. 
The game can be played against another human player, an 'easy' computer, or a 'hard' computer. 

How to play: 


More about the implementation: 
The project is built upon object-oriented programing where class objects create the premise of the game. 
The human player simply takes two player class objects which will take turns to play the game. 
The 'easy' computer takes a simple algorithm of locating first open position to make move. 
The 'hard' computer uses the minimax algorithm implemented with recursion to make move. 
Due to the scaling of the minimax algorithm, scaffolds of too large size may not work well with the 'hard' computer. 
