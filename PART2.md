# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtube.com).

## Minimum Requirements

### Completed

List all the features completed.

1. Randomised game board based on user input
2. Alien’s movement 
(alien’s direction -up, down, left, right
 Alien stop when encounter border/rock/zombies, alien hits and attack zombie, combo attack )
3. Game objects 
(Arrow- to change direction of movement, Rock- stop alien movement, Trail - reset to random game objects, health -add 20 life to alien,
Pod -10 damage to zombies,  Arrow -add 20 attacks to alien )
4. Life and attack of zombies and alien changes throughout the game
5. Game controls 
(switch direction of arrow, save game
load game, quit game, help command) 


## Additional Features

Object b which stands for "brain" is implemented. When zombies move to the location containing brain, zombies eat the brain and clones itself to another zombie. Alien in this case, is not affected when it encounters brain object. If encounter by alien, alien clears the brain to prevent zombie from getting cloned.

## Contributions


### Poh Ern Qi

1. Randomly generate game board.
2. *add more*

### Tan Jia Jin

1. Zombie movement and attack behaviour.
2. *add more*



## Problems Encountered & Solutions

1. Alien does not move after the user enters the command. Solution: pass the function to set the alien using vector.

2. Several zombies are not displayed on board based on user input. Solution: we check whether the rows and columns of zombies are empty first (in case the rows and columns generated have already been occupied by the alien). If it's empty, put the zombies in the assigned rows and columns on the board. If it is not empty, we minus the counter (i) by 1 (i-1) to make sure we get the same zombie in the next iteration and randomise the rows and columns again.


