// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT5L
// Names: TAN JIA JIN | POH ERN QI
// IDs: 1211101800 | 1211101398 
// Emails: 1211101800@student.mmu.edu.my | 1211101398@student.mmu.edu.my 
// Phones: 0189774517| 01110987289 | 
// *********************************************************


#include <iostream>
#include <string>
#include <vector>
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <array>
#include <conio.h> //for getch()
using namespace std;

//class zombie
class Zombie
{
public:
    int zombieLife;
    int zombieAttack;
    int zombieRange;
    int zombieRow;
    int zombieCol;
};

void displayZombieInfo(int zombieCount, Zombie z[], bool randomFlag)
{

    for (int i = 0; i < zombieCount; i++)
    {
        if (randomFlag)
        {
            z[i].zombieLife = rand() % 101 + 150; // range starting from 150 to 250
            z[i].zombieAttack = rand() % 16 + 15; // range starting from 15 to 30
            z[i].zombieRange = rand() % 5 + 1;    // range starting from 1 to 5
        }

        cout << "zombie " << i + 1 << "  "
             << "Life: " << z[i].zombieLife << "  "
             << "Attack: " << z[i].zombieAttack << "  "
             << "Range: " << z[i].zombieRange << endl;
    }
}


//class alien
class Alien
{
public:
    int alienLife;
    int alienAttack;
    void displayAlienInfo();
};
void Alien::displayAlienInfo()
{
    alienLife = 100;
    alienAttack = 0;
    cout << "Alien     "
         << "Life: " << alienLife << "  Attack: " << alienAttack << endl;
}


//class board
class Board
{
public:
    vector<vector<string>> map_; 
    int col_, rows_;             

public:
    Board(int col, int rows);
    void init(int col, int rows);
    void display() const;
    void setAlien(int &alienRow, int &alienCol);
    void moveLeft(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection);
    void moveRight(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection);
    void moveDown(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection);
    void moveUp(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection);
    void setZombie(int n, Zombie z[]);
    void setRandom();
    void reset();
    void command(int &alienRow, int &alienCol, int zombieCount, bool &quitFlag, Zombie z[], Alien a);
};

Board::Board(int col, int rows)
{
    init(col, rows);
}
void Board::init(int col, int rows)
{
    col_ = col;
    rows_ = rows;

    // create dynamic 2D array using vector
    map_.resize(rows_); // create empty rows
    for (int i = 0; i < rows_; ++i)
    {
        map_[i].resize(col_); // resize each row
    }
}
void Board::display() const
{

    cout << endl
         << " --__--__--__--__--__--__--__--_" << endl;
    cout << "      = Alien Vs Zombie =" << endl;
    cout << " __--__--__--__--__--__--__--__-" << endl
         << endl;

    // for each row
    for (int i = 0; i < rows_; ++i)
    {
        // display spaces in front of each row
        cout << " ";

        for (int j = 0; j < col_; ++j)
        {
            cout << "+-";
        }
        // end +- with +
        cout << "+" << endl; 

        // display row number 5 4 3 2 1 // use setw(2) to set width 2 in front
        cout << (rows_ - i);

        // display cell content and border of each column
        for (int j = 0; j < col_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        // end with |
        cout << "|" << endl; 
    }

    // display lower border (+-) of the last row
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        cout << setw(2) << "+-";
    }
    cout << "+" << endl;

    // display column number 111111..
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }

    // display last column 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5..
    cout << endl;
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

// set alien position
void Board::setAlien(int &alienRow, int &alienCol)
{
    string alien_position = "A";

    // set string "A" location using vector
    map_[alienRow][alienCol] = alien_position; 
}


//alien moveleft
void Board::moveLeft(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection )
{
    // set aliencol >0 to prevent exceeding the border
    if (alienCol > 0) 

    {
        // alienCol -1 represent the object at the left side of the alien, in this case is "r"
        if (map_[alienRow][alienCol - 1] == "r") 
        {
            string objects[] = {"health pack", "pod", "nothing", "arrow"};
            int noOfObjects = size(objects);

            // rand() randomize the objects in the array
            int randObj = rand() % noOfObjects; 
            cout << "Alien stumbles upon a rock." << endl;
            cout << "Alien discovers " << objects[randObj] << " beneath a rock." << endl;

            // if the randomize object is health pack
            if (objects[randObj] == "health pack") 
            {
                // change the "r" object to "h"
                map_[alienRow][alienCol - 1] = "h"; 
            }
            else if (objects[randObj] == "pod")
            {
                map_[alienRow][alienCol - 1] = "p";
            }
            else if (objects[randObj] == "nothing")
            {
                map_[alienRow][alienCol - 1] = " ";
            }
            else
            {
                string arrowObjects[] = {"^", "v", "<", ">"};
                int noOfArrowObjects = size(arrowObjects);
                int randObj = rand() % noOfArrowObjects;
                map_[alienRow][alienCol - 1] = arrowObjects[randObj];
            }

            // alienrow remains the same
            alienRow = alienRow; 
            // aliencol remains the same
            alienCol = alienCol; 
            // stop move set to true to prevent from moving in same direction
            stopMove = true;     

        }
        else if (map_[alienRow][alienCol - 1] == "p")
        {
            // temporary randomize first
            int r_zombie = rand() % zombieCount + 1; 
            cout << "Alien finds a pod." << endl;
            map_[alienRow][alienCol] = ".";

            alienRow = alienRow;
            // move the alien to left
            alienCol = alienCol - 1; 
        }
        else if (map_[alienRow][alienCol - 1] == "h")
        {
            cout << "Alien finds a health pack." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;
        }
        else if (map_[alienRow][alienCol - 1] == " ")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;
        }
        else if (map_[alienRow][alienCol - 1] == "^")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;

            // set changedirection flag to true to change direction
            changeDirection = true; 
            // stop move=true prevent from moving in same direction
            stopMove = true; 
            // set the command to up      
            command = "u";          
        }
        else if (map_[alienRow][alienCol - 1] == "v")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;
            changeDirection = true;
            stopMove = true;
            command = "d";
        }
        else if (map_[alienRow][alienCol - 1] == "<")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;
            changeDirection = true;
            stopMove = true;
            command = "l";
        }
        else if (map_[alienRow][alienCol - 1] == ">")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;
            changeDirection = true;
            stopMove = true;
            command = "r";
        }
        else if (map_[alienRow][alienCol - 1] == ".")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol - 1;
            changeDirection = true;
            stopMove = true;
            command = "l";
        }
    }
    else
    {
        cout << "Alien hits a border." << endl;
        cout << "Alien's turn ends. The trail is reset." << endl;
        // stop moving when hit border
        stopMove = true; 
    }
}

//alien moveright
void Board::moveRight(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection)
{
    if (alienCol < col_ - 1)
    {
        if (map_[alienRow][alienCol + 1] == "r")
        {
            string objects[] = {"health pack", "pod", "nothing", "arrow"};
            int noOfObjects = size(objects);
            int randObj = rand() % noOfObjects;
            cout << "Alien stumbles upon a rock." << endl;
            cout << "Alien discovers " << objects[randObj] << " beneath a rock." << endl;

            if (objects[randObj] == "health pack")
            {
                map_[alienRow][alienCol + 1] = "h";
            }
            else if (objects[randObj] == "pod")
            {
                map_[alienRow][alienCol + 1] = "p";
            }
            else if (objects[randObj] == "nothing")
            {
                map_[alienRow][alienCol + 1] = " ";
            }
            else
            {
                string arrowObjects[] = {"^", "v", "<", ">"};
                int noOfArrowObjects = size(arrowObjects);
                int randObj = rand() % noOfArrowObjects;
                map_[alienRow][alienCol + 1] = arrowObjects[randObj];
            }
            alienRow = alienRow;
            alienCol = alienCol;
            stopMove = true;
        }
        else if (map_[alienRow][alienCol + 1] == "p")
        {
            int r_zombie = rand() % zombieCount + 1;
            cout << "Alien finds a pod." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
        }
        else if (map_[alienRow][alienCol + 1] == "h")
        {
            cout << "Alien finds a health pack." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
        }
        else if (map_[alienRow][alienCol + 1] == " ")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
        }
        else if (map_[alienRow][alienCol + 1] == "^")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
            changeDirection = true;
            stopMove = true;
            command = "u";
        }
        else if (map_[alienRow][alienCol + 1] == "v")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
            changeDirection = true;
            stopMove = true;
            command = "d";
        }
        else if (map_[alienRow][alienCol + 1] == "<")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
            changeDirection = true;
            stopMove = true;
            command = "l";
        }
        else if (map_[alienRow][alienCol + 1] == ">")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
            changeDirection = true;
            stopMove = true;
            command = "r";
        }
        else if (map_[alienRow][alienCol + 1] == ".")
        {
            cout << "Alien discovers nothing." << endl;

            map_[alienRow][alienCol] = ".";
            alienRow = alienRow;
            alienCol = alienCol + 1;
            changeDirection = true;
            stopMove = true;
            command = "r";
        }
    }
    else
    {
        cout << "Alien hits a border." << endl;
        cout << "Alien's turn ends. The trail is reset." << endl;
        stopMove = true;
    }
}

//alien movedown
void Board::moveDown(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection)
{
    if (alienRow < rows_ - 1)
    {
        if (map_[alienRow + 1][alienCol] == "r")
        {
            string objects[] = {"health pack", "pod", "nothing", "arrow"};
            int noOfObjects = size(objects);
            int randObj = rand() % noOfObjects;
            cout << "Alien stumbles upon a rock." << endl;
            cout << "Alien discovers " << objects[randObj] << " beneath a rock." << endl;

            if (objects[randObj] == "health pack")
            {
                map_[alienRow + 1][alienCol] = "h";
            }
            else if (objects[randObj] == "pod")
            {
                map_[alienRow + 1][alienCol] = "p";
            }
            else if (objects[randObj] == "nothing")
            {
                map_[alienRow + 1][alienCol] = " ";
            }
            else
            {
                string arrowObjects[] = {"^", "v", "<", ">"};
                int noOfArrowObjects = size(arrowObjects);
                int randObj = rand() % noOfArrowObjects;
                map_[alienRow + 1][alienCol] = arrowObjects[randObj];
            }
            alienRow = alienRow;
            alienCol = alienCol;
            stopMove = true;
        }
        else if (map_[alienRow + 1][alienCol] == "p")
        {
            int r_zombie = rand() % zombieCount + 1;
            cout << "Alien finds a pod." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
        }
        else if (map_[alienRow + 1][alienCol] == "h")
        {
            cout << "Alien finds a health pack." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
        }
        else if (map_[alienRow + 1][alienCol] == " ")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
        }
        else if (map_[alienRow + 1][alienCol] == "^")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
            changeDirection = true;
            stopMove = true;
            command = "u";
        }
        else if (map_[alienRow + 1][alienCol] == "v")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
            changeDirection = true;
            stopMove = true;
            command = "d";
        }
        else if (map_[alienRow + 1][alienCol] == "<")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
            changeDirection = true;
            stopMove = true;
            command = "l";
        }
        else if (map_[alienRow + 1][alienCol] == ">")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
            changeDirection = true;
            stopMove = true;
            command = "r";
        }
        else if (map_[alienRow + 1][alienCol] == ".")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow + 1;
            changeDirection = true;
            stopMove = true;
            command = "d";
        }
        else
        {

        }
    }
    else
    {
        cout << "Alien hits a border." << endl;
        cout << "Alien's turn ends. The trail is reset." << endl;
        stopMove = true;
    }
}

//alien move up
void Board::moveUp(int &alienRow, int &alienCol, int zombieCount, bool &stopMove, string &command, bool &changeDirection)
{
    if (alienRow > 0)
    {
        if (map_[alienRow - 1][alienCol] == "r")
        {
            string objects[] = {"health pack", "pod", "nothing", "arrow"};
            int noOfObjects = size(objects);
            int randObj = rand() % noOfObjects;
            cout << "Alien stumbles upon a rock." << endl;
            cout << "Alien discovers " << objects[randObj] << " beneath a rock." << endl;

            if (objects[randObj] == "health pack")
            {
                map_[alienRow - 1][alienCol] = "h";
            }
            else if (objects[randObj] == "pod")
            {
                map_[alienRow - 1][alienCol] = "p";
            }
            else if (objects[randObj] == "nothing")
            {
                map_[alienRow - 1][alienCol] = " ";
            }
            else
            {
                string arrowObjects[] = {"^", "v", "<", ">"};
                int noOfArrowObjects = size(arrowObjects);
                int randObj = rand() % noOfArrowObjects;
                map_[alienRow - 1][alienCol] = arrowObjects[randObj];
            }
            alienRow = alienRow;
            alienCol = alienCol;
            stopMove = true;
        }
        else if (map_[alienRow - 1][alienCol] == "p")
        {
            int r_zombie = rand() % zombieCount + 1;
            cout << "Alien finds a pod." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;

        }
        else if (map_[alienRow - 1][alienCol] == "h")
        {
            cout << "Alien finds a health pack." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;

        }
        else if (map_[alienRow - 1][alienCol] == " ")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;
            
        }
        else if (map_[alienRow - 1][alienCol] == "^")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;
            changeDirection = true;
            stopMove = true;
            command = "u";

        }
        else if (map_[alienRow - 1][alienCol] == "v")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;
            changeDirection = true;
            stopMove = true;
            command = "d";

        }
        else if (map_[alienRow - 1][alienCol] == "<")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;
            changeDirection = true;
            stopMove = true;
            command = "l";

        }
        else if (map_[alienRow - 1][alienCol] == ">")
        {
            cout << "Alien discovers an arrow." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;
            changeDirection = true;
            stopMove = true;
            command = "r";

        }
        else if (map_[alienRow - 1][alienCol] == ".")
        {
            cout << "Alien discovers nothing." << endl;
            map_[alienRow][alienCol] = ".";
            alienCol = alienCol;
            alienRow = alienRow - 1;
            changeDirection = true;
            stopMove = true;
            command = "u";

        }
    }
    else
    {
        cout << "Alien hits a border." << endl;
        cout << "Alien's turn ends. The trail is reset." << endl;
        stopMove = true;
    }
}

// set zombie position in board
void Board::setZombie(int n, Zombie z[])
{
    string zombie[n];

    for (int i = 1; i <= n; i++)
    {

        zombie[i - 1] = to_string(i);
    }

    for (int i = 0; i < n; i++)
    {

        int r_random = rand() % rows_;
        int c_random = rand() % col_;

        if (!map_[r_random][c_random].empty()) // if rows and columns is not empty
        {
            i = i - 1;
            continue; // take the same zombie and do another randomize
        }
        else
        {
            map_[r_random][c_random] = zombie[i]; // set rows and columns to each zombie
            z[i].zombieRow = r_random;
            z[i].zombieCol = c_random;
        }
    }
}


// set the game objects position
void Board::setRandom()
{
    string objects[] = {"h", "p", "r", "v", "^", "<", ">", " ", " ", " ", "r", " "};
    int noOfObjects = size(objects);

    // put random game objects into the vector array
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < col_; ++j)
        {
            if (map_[i][j].empty())
            {
                int objNo = rand() % noOfObjects; //rand()obj in array string objects[]
                map_[i][j] = objects[objNo];
            }
        }
    }
}


//reset trail
void Board::reset()  
{
    string objects[] = {"h", "p", "r", "v", "^", "<", ">", " "};
    int noOfObjects = size(objects);
    for (int i = 0; i < rows_; ++i)
    {

        for (int j = 0; j < col_; ++j)
        {
            if (map_[i][j].compare(".") == 0)
            {
                int objNo = rand() % noOfObjects;
                map_[i][j] = objects[objNo];
            }
        }
    }
}

//users input command
void Board::command(int &alienRow, int &alienCol, int zombieCount, bool &quitFlag, Zombie z[], Alien a)
{
    string command;
    cout << endl
         << "Command>";
    cin >> command;

    bool stopMove = false;
    bool changeDirection = true;

    while (changeDirection)
    {
        changeDirection = false;
        stopMove = false;
        if (command == "l")
        {
            while (!stopMove) // while true
            {

                moveLeft(alienRow, alienCol, zombieCount, stopMove, command, changeDirection);
                setAlien(alienRow, alienCol);

                cout << endl
                     << "Press any key to continue...." << endl;
                getch();

                if (stopMove == true && changeDirection == false)
                {
                    reset(); //reset the trail
                }

                display();

                a.displayAlienInfo();

                displayZombieInfo(zombieCount, z, false);
            }
        }
        else if (command == "r")
        {
            while (!stopMove)
            {

                moveRight(alienRow, alienCol, zombieCount, stopMove, command, changeDirection);
                setAlien(alienRow, alienCol);

                cout << endl
                     << "Press any key to continue...." << endl;

                getch();
                if (stopMove == true && changeDirection == false)
                {
                   reset();
                }
                display();

                a.displayAlienInfo();

                displayZombieInfo(zombieCount, z, false);
            }
        }
        else if (command == "d")
        {
            while (!stopMove)
            {
                moveDown(alienRow, alienCol, zombieCount, stopMove, command, changeDirection);
                setAlien(alienRow, alienCol);

                cout << endl
                     << "Press any key to continue...." << endl;
                getch();
                if (stopMove == true && changeDirection == false)
                {
                   reset();
                }
                display();

                a.displayAlienInfo();

                displayZombieInfo(zombieCount, z, false);
            }
        }
        else if (command == "u")
        {
            while (!stopMove)
            {

                moveUp(alienRow, alienCol, zombieCount, stopMove, command, changeDirection);
                setAlien(alienRow, alienCol);

                cout << endl
                     << "Press any key to continue...." << endl;
                getch();
                if (stopMove == true && changeDirection == false)
                {
                   reset();
                }
                display();

                a.displayAlienInfo();

                displayZombieInfo(zombieCount, z, false);
            }
        }
        else if (command == "q")
        {
            quitFlag = true;
            changeDirection = false;
            stopMove = true;
        }
        else if (command == "help")
        {
            cout << "u        -Alien to move up." << endl;
            cout << "d      -Alien to move down." << endl;
            cout << "l      -Alien to move left." << endl;
            cout << "r     -Alien to move right." << endl;
            cout << "arrow     -Switch the direction of an arrow object in the game board." << endl;
            cout << "help      -Display the user commands." << endl;
            cout << "save      -Save the current game." << endl;
            cout << "load      -Load the game." << endl;
            cout << "quit      -Quit the game." << endl;

            display();
            a.displayAlienInfo();

            displayZombieInfo(zombieCount, z, false);
        }
    }
}



// main menu
void display(int rows, int col, int zombieCount)
{
    cout << endl
         << "Default Game Setting" << endl;
    cout << "----------------------" << endl;
    cout << "Board Rows: " << rows << endl;
    cout << "Board Columns: " << col << endl;
    cout << "Zombie Count: " << zombieCount << endl;

    bool ans = true;
    while (ans)
    {
        string x;
        cout << "Do you wish to change the game settings(y/n): ";
        ;
        cin >> x;
        if (x == "y")
        {
            ans = false;
            cout << endl
                 << "Board Settings" << endl;
            cout << "---------------" << endl;
            cout << "Enter rows=> ";
            cin >> rows;
            cout << "Enter columns=> ";
            cin >> col;
            cout << endl
                 << "Zombie Settings" << endl;
            cout << "---------------" << endl;
            cout << "Enter number of zombies=> ";
            cin >> zombieCount;
            cout << endl
                 << "Setting Updated." << endl;
            display(rows, col, zombieCount);
        }
        else if (x == "n")
        {
            ans = false;

            bool quitFlag = false;
            Board b(col, rows);
            
            // to set the alien at the center of board
            int alienRow;
            int alienCol;
            alienRow = (rows - 1) / 2;      
            alienCol = (col - 1) / 2;      

            // pass alienRow and alienCol to setAlien function
            b.setAlien(alienRow, alienCol); 

            //pass no. of zombie set by user to set zombie on the board
            Zombie z[zombieCount];
            b.setZombie(zombieCount, z);

            //set random game objects and display the board
            b.setRandom();
            b.display();

            //display alien info and zombieinfo
            Alien a;
            a.displayAlienInfo();
            displayZombieInfo(zombieCount, z, true);

            while (!quitFlag)
            {
                b.command(alienRow, alienCol, zombieCount, quitFlag, z, a);
            }
        }
        //if users enters other than "y"/"n"
        else
        {
            cout << "Invalid input, please try again." << endl;
        }
    }
}

int main()
{
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    srand(time(NULL));
    int rows = (2 * rand()) % 16 + 1;
    int col = (2 * rand()) % 16 + 1;
    int zombieCount = 1 + (2 * rand()) % 10;

    display(rows, col, zombieCount);
   
}