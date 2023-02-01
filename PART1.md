# Part 1


## Video Demo


The [Video Demo](https://youtu.be/96-Bz1h0nlc) of the game.




## Minimum Requirements
### Completed
1. Randomised game board based on user input
2. Alien’s movement 
(parts that have completed: alien’s direction -up, down, left, right
 Alien stop when encounter border/ rock)
3. Game objects 
(parts that have completed: Arrow- to change direction of movement,
  Rock- stop alien movement, Trail - reset to random game objects )




### To Do
1. Life and attack of zombies and alien
2. Alien’s movement 
(parts that have not completed: alien hits and attack zombie)
3. Game objects 
(parts that have not completed: health -add 20 life to alien,
Pod -10 damage to zombies,  Arrow -add 20 attacks to alien)
4. Game controls 
(parts not completed: - switch direction of arrow, -save game
-load game, -quit game) 




## Additional Features
Currently the additional features have not been implemented.


## Contributions
### Tan Jia Jin
1. Randomly generate game board.
2. Game objects (trail)


### Poh Ern Qi
1. Alien’s movement
2. Game objects (arrow, rock)




## Problems Encountered & Solutions
Describe the problems encountered and provide the solutions / plan for the solutions.


1. Alien does not move after the user enters the command. 
Solution: pass the function to set the alien using vector.


2. Several zombies are not displayed on board based on user input.
Solution: we check whether the rows and columns of zombies are empty first (in case the rows and columns generated have already been occupied by the alien). If it's empty, put the zombies in the assigned rows and columns on the board. If it is not empty, we minus the counter (i) by 1 (i-1) to make sure we get the same zombie in the next iteration and randomise the rows and columns again.