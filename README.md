# Alien vs. Zombie


Please introduce the game here.


Alien vs Zombie is a Puzzle and Strategy game. Players can customize the row and columns of the board and the number of zombie in the board. Players must destroy the zombies by cleverly manoeuvring the aliens on a path using strategy. To win, you must kill every zombie on the board. Since there is just one attack per round, you can prevent dying by defeating the zombie down as quickly as possible. The object in the board can help u in defeating the zombie, you will succeed in the game, if you make good use of the board's elements.
[![Screenshot of the game](https://imgur.com/a/48M7d1N)](https://imgur.com/a/48M7d1N)


This is the [Video Demo](https://youtu.be/96-Bz1h0nlc) of the game.




## Compilation Instructions

1. Download the whole repository (alien-vs-zombie) as a zip file.


2. Head over to the downloads folder, right click on the folder and click extract all. Then click extract.


3. Once the file is extracted, open command prompt to change the current directory by entering 

```
   cd Downloads\alien-vs-zombie-master\alien-vs-zombie-master 
```
```
4. To generate an executable file. Enter 
```
   g++ -o part1.exe part1.cpp
```   
5. Run the file that you just created by entering
```
part1.exe
```




## User Manual
Alien vs Zombie is a turn-based combat game in which the player controls Alien to defeat a group of Zombies. 


How to Play


For every round of the game, the player will have the option to input the number of rows, columns and number of zombies for the game board.  After the input has been set by the user, the game will display the game board based on the inputs set by the user. For example, if the user specifies the number of rows to be 3, number of columns to be 15 and number of zombies to be 2, the game will then generate the game board containing 3 rows, 15 columns and 2 zombies. After the board is generated, you will be able to see a command for the user to enter the input. The input entered by the user can control the alien by specifying the directions for the alien to move. Here are the lists of commands for the user:


Lists of Commands:


1. u                           - Alien moves up
2. d                          - Alien moves down
3. l                           - Alien moves left
4. r                         - Alien moves right
5. Help                          - List the available commands for the user




Alien Movement


Once users enters the command, Alien moves in the game board according to the command. Alien will continue to move in the same direction and will only stop once it hits the border of the game board, or when it hits the rock object.  When alien is moving, it leaves a dotted trail indicating the path that has been passed by the alien. Once it stops, the dotted trail will reset to random game objects. If the alien has encountered an arrow, it will change the direction of its movement. For example, suppose that the alien has encountered an up arrow. The up arrow will change its direction of movement of the alien to an upward direction.  Here are the descriptions of game objects available in the game board:




Game Objects


1. Arrow (^  v  <  >)    
 -Changes the direction of movement of alien


2. Health (h)               
 -Adds 20 life to alien.


3. Pod (p)               
 -Instantly inflicts 10 damage to Zombie when hit by Alien.


4. Rock (r)                  
 - Reveals randomised game objects when encounter by the alien


5. Empty 
-Empty space on the board


6. Trail (.) 
-Left by alien when it moves
-Reset to random game objects when the alien stops and its turn ends.




## Progress Log
- [Part 1](PART1.md)
- [Part 2](PART2.md)


## Contributors
- Tan Jia Jin
- Poh Ern Qi
