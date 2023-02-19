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
(switch direction of arrow,  help command) 
6. Save and load Game file


## Additional Features

Object b which stands for "brain" is implemented. When zombies move to the location containing brain, zombies eat the brain and clones itself to another zombie. Alien in this case, is not affected when it encounters brain object. If encounter by alien, alien clears the brain to prevent zombie from getting cloned.

## Contributions


### Poh Ern Qi

1. Alien’s movement
2. Game objects (arrow, rock, pod, heath)
4. Additional Features

### Tan Jia Jin

1. Randomly generate game board.
2. Game objects (trail)
3. Save and load game file


## Problems Encountered & Solutions
### Problems 1:
Alien does not move after the user enters the command. 

Solution: pass the function to set the alien using vector.

### Problems 2:
Several zombies are not displayed on board based on user input. 

Solution: we check whether the rows and columns of zombies are empty first (in case the rows and columns generated have already been occupied by the alien). If it's empty, put the zombies in the assigned rows and columns on the board. If it is not empty, we minus the counter (i) by 1 (i-1) to make sure we get the same zombie in the next iteration and randomise the rows and columns again.

### Problems 3:
While saving the map_ vector to a text file, all the elements in the vector are successfully saved, but when loading the text file, the space character " " is not recognized and is treated as a delimiter, resulting in incorrect loading of the vector elements.

Solution: To resolve this issue, I decided to use a comma as a delimiter while saving the map_ vector to the text file. This way, when loading the text file, the comma delimiter can be used to correctly separate the vector elements. Using a different delimiter ensures that spaces within the elements are preserved and do not cause any issues while loading the data. By updating the delimiter, the data can be saved and loaded correctly without any loss of information.

### Problem 4:
When my initial zombiecount is smaller than the load in zombiecount, I encountered an error: Exception has occurred. Segmentation fault.

Solution: To solve the issue, I used a pointer zombie \*z instead of the original array to store the zombie objects. By doing this, I can dynamically allocate memory for the array using new and delete when needed. This allows the array to be enlarge to avoid the Segmentation fault error. Example : zombie \*z = new zombie[newZombieCount]; After using the array, I freed the memory using: delete[] z;

### Problem 5:

