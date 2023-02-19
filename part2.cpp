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
#include <vector>
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <conio.h> //for //getch()
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;

// class zombie
class Zombie
{
public:
    int zombieLife;
    int zombieAttack;
    int zombieRange;
    int zombieRow;
    int zombieCol;
    string zombieStatus = "a"; //a indicates zombie alive
    string zombieNo;
};

// class alien
class Alien
{
public:
    int alienLife = 100;
    int alienAttack = 0;
	int alienRow;
    int alienCol;
};

// class board
class Board
{
public:
    vector<vector<string>> map_;
    bool isAlienTurn_ = false;
    int col_, rows_;
	int currentZombieTurnIndex_ = -1;


public:
    Board(int col, int rows);
    void init(int col, int rows);
    void displayGameHeader();
    void displayGameContent(int rows, int col, int zombieCount);
    void setAlien(Alien alien);
    void displayAlienInfo(Alien alien);
    void displayZombieInfo(int zombieCount, Zombie z[]);
    void displayPlayAgainMenu();
    void move(int zombieCount, bool &stopMove, string &command, bool &changeDirection, Alien &a, Zombie z[], string movement);
    void setZombie(int zombieCount, Zombie z[]);
    void setRandom();
    void reset();
    void command(int &zombieCount, bool &quitFlag, Zombie (&z)[], Alien &a);
};

// Save function
void save(Board &b, Alien a, Zombie z[], int zombieCount)
{
    string filename;
    cout << "Enter File name to save the current game: ";
    cin >> filename;
    ofstream outfile;
    outfile.open(filename);
    // If fail to open the file
    if (outfile.fail())
    {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    // Write the size of the vector to the file
    outfile << b.rows_ << " " << b.col_ << endl;

    // Write each element of the vector to the file
    for (int i = 0; i < b.rows_; i++)
    {
        for (int j = 0; j < b.col_; j++)
        {
            outfile << b.map_[i][j] << ",";
        }
        outfile << endl;
    }

    // Write the Alien's life and attack values to the file
    outfile << a.alienLife << " " << a.alienAttack  << " " << a.alienRow  << " " << a.alienCol << endl;

    // Write the Zombie objects' values to the file
    outfile << zombieCount << endl;
    for (int i = 0; i < zombieCount; i++)
    {
        outfile << z[i].zombieLife << " " << z[i].zombieAttack << " " << z[i].zombieRange << " " << z[i].zombieRow << " " << z[i].zombieCol << " " << z[i].zombieStatus << " " << z[i].zombieNo << endl;
    }
    outfile.close();
    cout << endl
         << "Successfully saved the game to file :" << filename << endl
         << "Press any key to continue...." << endl;
    getch();
}

// Load function
void load(Board &b, Alien &a, Zombie (&n)[], int &zombieCount)
{
    string filename;
    cout << "Enter File name =>";
    cin >> filename;
    ifstream infile;
    // If file fail to open
    infile.open(filename);
    if (!infile.is_open())
    {
        cout << "Failed to open the file " << filename << endl;
        return;
    }
    // Read the size of the vector from the file
    int rows, cols;
    infile >> rows >> cols;

    // Resize the map vector to the correct size
    b.init(cols, rows);

    // read the board data
    string line;
    getline(infile, line); // skip the rest of the line
    for (int i = 0; i < rows; i++)
    {
        getline(infile, line);
        istringstream iss(line);
        for (int j = 0; j < cols; j++)
        {
            string cell;
            getline(iss, cell, ',');
            b.map_[i][j] = cell[0];
        }
    }

    // Read the alien's data from the file
    infile >> a.alienLife >> a.alienAttack >> a.alienRow >> a.alienCol;;

    // Read the zombie data from the file
    int newzombiecount;
    infile >> newzombiecount;
    Zombie *z = new Zombie[newzombiecount];
    for (int i = 0; i < newzombiecount; i++)
    {
        infile >> z[i].zombieLife >> z[i].zombieAttack >> z[i].zombieRange >> z[i].zombieRow >> z[i].zombieCol >> z[i].zombieStatus >> z[i].zombieNo;
    }
    for (int i = 0; i < newzombiecount; i++)
    {
        n[i].zombieLife = z[i].zombieLife;
        n[i].zombieAttack = z[i].zombieAttack;
        n[i].zombieRange = z[i].zombieRange;
        n[i].zombieRow = z[i].zombieRow;
        n[i].zombieCol = z[i].zombieCol;
        n[i].zombieStatus = z[i].zombieStatus;
        n[i].zombieNo = z[i].zombieNo;
    }
    zombieCount = newzombiecount;
    delete[] z;
    infile.close();

    cout << endl
         << filename << " is succesfully loaded!" << endl
         << "Press any key to continue...." << endl;
    getch();
}

Board::Board(int col, int rows)
{
    init(col, rows);
}
void Board::init(int col, int rows)
{
    col_ = col;
    rows_ = rows;
    isAlienTurn_=true;
	currentZombieTurnIndex_=-1;

    //  iterates through each row and clears the content of that row
    for (auto &row : map_)
    {
        // clear each row
        row.clear();
    }
    // clear the vector itself
    map_.clear();

    // create dynamic 2D array using vector
    map_.resize(rows_); // create empty rows
    for (int i = 0; i < rows_; ++i)
    {
        map_[i].resize(col_);
    }
}
void Board::displayGameHeader()
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

        // display row number 5 4 3 2 1 
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

void Board::displayGameContent(int rows, int col, int zombieCount)
{
    cout << endl
         << "Default Game Setting" << endl;
    cout << "----------------------" << endl;
    cout << "Board Rows: " << rows << endl;
    cout << "Board Columns: " << col << endl;
    cout << "Zombie Count: " << zombieCount << endl;

    bool continueMenu = true;
    bool validRow = false; // check validity of row if row is odd= true
    bool validCol = false;
    bool validZombieCount = false;
    string input;
    while (continueMenu)
    {
        cout << "Do you wish to change the game settings(y/n): ";
        cin >> input;
        if (input == "y")
        {

            continueMenu = false; // quit menu after display
            cout << endl
                 << endl
                 << "Board Settings" << endl;
            cout << "---------------" << endl;

            while (!validRow)
            {
                cout << "Enter rows=> ";
                cin >> rows;
                if (rows % 2 == 0)
                    cout << "You entered " << rows << " for number of rows. Only odd number is allowed." << endl;
                else
                    validRow = true;
            }

            while (!validCol)
            {
                cout << "Enter columns=> ";
                cin >> col;
                if (col % 2 == 0)
                    cout << "You entered " << col << " for number of columns. Only odd number is allowed." << endl;
                else
                    validCol = true;
            }
            cout << endl
                 << "Zombie Settings" << endl;
            cout << "---------------" << endl;

            while (!validZombieCount)
            {
                cout << "Enter number of zombies=> ";
                cin >> zombieCount;
                if (zombieCount >= rows * col)  //prevent user from setting zombie count more than total spaces available
                {
                    cout << "Number of zombies should be less than " << rows * col << "." << endl; 
                }
                else if (zombieCount >= 10)
                {
                    cout << "Number of zombies should be less than 10." << endl;
                }
                else
                    validZombieCount = true;
            }

            cout << endl
                 << "Setting Updated." << endl;
            init(col, rows);
            displayGameContent(rows, col, zombieCount);
        }
        else if (input == "n")
        {
            continueMenu = false; // quit menu after display

            bool quitFlag = false;

            // to set the alien at the center of board
            int alienRow = (rows - 1) / 2;
            int alienCol = (col - 1) / 2;
            init(col, rows);
			
			Alien a = Alien(); 
			a.alienRow = alienRow;
			a.alienCol = alienCol;
            setAlien(a);

            Zombie z[col * rows - 1]; 
            setZombie(zombieCount, z);
            // set random game objects and display the board
            setRandom();
            int newZombieCol = 0;
            int newZombieRow = 0;
            bool isBorder = true;
            bool nextMoveIsZombie = true; // check if next position is zombie
            string movement = "";
            bool continueMove = true;


            while (!quitFlag)
            {
                isAlienTurn_ = true;
				currentZombieTurnIndex_ = -1;
                displayGameHeader();
                displayAlienInfo(a);
                displayZombieInfo(zombieCount, z);

                command(zombieCount, quitFlag, z, a);

                for (int i = 0; i < zombieCount; i++)
                {
                    isAlienTurn_ = false;
					currentZombieTurnIndex_ = i;
                    isBorder = true;
                    if (z[i].zombieStatus != "d")
                    {
                        string randMove[] = {"left", "right", "up", "down"};
                        int noOfObjects = size(randMove);
                        int randObj = rand() % noOfObjects;

                        if (randMove[randObj] == "left")
                        {
                            newZombieCol = z[i].zombieCol - 1;
                            newZombieRow = z[i].zombieRow;
                            movement = "left";
                            if (z[i].zombieCol > 0)
                                isBorder = false;
                        }
                        else if (randMove[randObj] == "right")
                        {
                            newZombieCol = z[i].zombieCol + 1;
                            newZombieRow = z[i].zombieRow;
                            movement = "right";
                            if (z[i].zombieCol < col - 1)
                                isBorder = false;
                        }
                        else if (randMove[randObj] == "up")
                        {
                            newZombieCol = z[i].zombieCol;
                            newZombieRow = z[i].zombieRow - 1;
                            movement = "up";
                            if (z[i].zombieRow > 0)
                                isBorder = false;
                        }
                        else if (randMove[randObj] == "down")
                        {
                            newZombieCol = z[i].zombieCol;
                            newZombieRow = z[i].zombieRow + 1;
                            movement = "down";
                            if (z[i].zombieRow < rows - 1)
                                isBorder = false;
                        }

                        if (!isBorder)
                        {
                            nextMoveIsZombie = false;
                            bool is_valid = true;
                            for (const char &c : map_[newZombieRow][newZombieCol])
                            { // iterating over the characters in a string in 2d array
                                if (!isdigit(c))
                                {
                                    is_valid = false;
                                    break;
                                }
                            }
                            if (is_valid)
                            {
                                int zombieNumber = 0;
                                try
                                {
                                    zombieNumber = std::stoi(map_[newZombieRow][newZombieCol]); // convert to int
                                    nextMoveIsZombie = true;
                                }
                                catch (std::exception &e) // If the string cannot be converted to an integer (non numeric)
                                {
                                    nextMoveIsZombie = false;
                                }
                            }
                            else
                                nextMoveIsZombie = false;
                        }
                        if (!isBorder && map_[newZombieRow][newZombieCol] != "A" && !nextMoveIsZombie) //check if next position is !border & not alien & not zombie
                        {
                            cout << endl
                                 << "Press any key to continue..."<<endl;
                             getch();
                            displayGameHeader();
                            isAlienTurn_ = false;
                            displayAlienInfo(a);
                            currentZombieTurnIndex_ = i;
                            displayZombieInfo(zombieCount, z);

                            continueMove = true;

                            if (map_[newZombieRow][newZombieCol] == "b") // When Zombie discovers brain
                            {
                                z[zombieCount].zombieRow = newZombieRow;
                                z[zombieCount].zombieCol = newZombieCol;
                                z[zombieCount].zombieStatus = "a";
                                z[zombieCount].zombieNo = to_string(zombieCount + 1);

                                // clone the current zombie's value to the new zombie
                                z[zombieCount].zombieLife = z[i].zombieLife;
                                z[zombieCount].zombieAttack = z[i].zombieAttack;
                                z[zombieCount].zombieRange = z[i].zombieRange;
                                map_[newZombieRow][newZombieCol] = z[zombieCount].zombieNo;

                                cout <<endl<< "Zombie " << z[i].zombieNo << " discovers brain when moved to the " << movement << "." << endl;
                                cout << "Zombie " << z[i].zombieNo << " eats the brain and clones itself to another zombie." << endl;

                                nextMoveIsZombie = true;
                                zombieCount = zombieCount + 1;
                                continueMove = false;
                            }

                            if (continueMove)
                            {
                                map_[z[i].zombieRow][z[i].zombieCol] = " ";
                                map_[newZombieRow][newZombieCol] = z[i].zombieNo;

                                z[i].zombieRow = newZombieRow;
                                z[i].zombieCol = newZombieCol;

                                cout <<endl<< "Zombie " << z[i].zombieNo << " moves to the " << movement << "." << endl;

                                double dist = sqrt(pow(z[i].zombieRow - alienRow, 2) + pow(z[i].zombieCol - alienCol, 2));
                                if (dist > z[i].zombieRange)
                                {
                                    cout << "Zombie " << z[i].zombieNo << " is unable to attack alien." << endl;
                                    cout << "Alien is too far." << endl;
                                }
                                else
                                {
                                    cout <<"Zombie " << z[i].zombieNo << " attacks alien." << endl;
                                    cout << "Alien receives a damage of " << z[i].zombieAttack << endl;
                                    a.alienLife = a.alienLife - (z[i].zombieAttack);
                                    if (a.alienLife > 0)
                                        cout << "Alien is still alive."<<endl;
                                    else
                                    {
                                        cout << "Alien is defeated. You lose!" << endl;
                                        displayPlayAgainMenu();
                                    }
                                }
                            }
                            cout << endl
                                 << "Press any key to continue..."<<endl;
                            getch();
                            displayGameHeader();
                            displayAlienInfo(a);
                            displayZombieInfo(zombieCount, z);
                        }
                        else
                        {
                            i = i - 1;
                            continue;
                        }
                    }
                }
                cout << endl
                     << "Press any key to continue..."<<endl;
                 getch();
            }
        }
        // if users enters other than "y"/"n"
        else
        {
            cout << "Invalid input, please try again." << endl;
        }
    }
}

// set alien position
void Board::setAlien(Alien alien)
{
    string alien_position = "A";

    // set string "A" location using vector
    map_[alien.alienRow][alien.alienCol] = alien_position;
}

void Board::displayAlienInfo(Alien alien)
{
   if(isAlienTurn_){  
		cout << std::setw(9) << " > Alien     " << std::setw(9) << "    Life: " << alien.alienLife << std::setw(9) << "     Attack: " << alien.alienAttack << endl;
   }else{
		cout << std::setw(9) << "   Alien     " << std::setw(9) << "    Life: " << alien.alienLife << std::setw(9) << "     Attack: " << alien.alienAttack << endl;
   }
}

void Board::displayZombieInfo(int zombieCount, Zombie n[])
{
    Zombie *x = new Zombie[zombieCount];
    for (int i = 0; i < zombieCount; i++)
    {
        x[i] = n[i];
    }
    int size = zombieCount;
    for (int i = 0; i < size; i++)
    {
        if(i == currentZombieTurnIndex_)  
			cout << std::setw(9) << ">  Zombie " << x[i].zombieNo << "  ";
		else 			
			cout << std::setw(9) << "   Zombie " << x[i].zombieNo << "  ";
		
		cout << std::setw(9) << "    Life: " << x[i].zombieLife << "  "
             << std::setw(9) << "    Attack: " << x[i].zombieAttack << "  "
             << std::setw(9) << "    Range: " << x[i].zombieRange << endl;
    }
    delete[] x;
}

// set zombie position in board
void Board::setZombie(int zombieCount, Zombie z[])
{
    int r_random = 0;
    int c_random = 0;
    int range_random = 0;
    bool correctRange = false;

    for (int i = 0; i < zombieCount; i++)
    {
        correctRange = false;

        r_random = rand() % rows_;
        c_random = rand() % col_;

        if (!map_[r_random][c_random].empty()) // if rows and columns is not empty
        {
            i = i - 1;
            continue; // take the same zombie and do another randomize
        }
        else
        {
            z[i].zombieRow = r_random;
            z[i].zombieCol = c_random;
            z[i].zombieNo = to_string(i + 1);
            z[i].zombieLife = rand() % 26 + 40;   // range starting from 40 to 65
            z[i].zombieAttack = rand() % 16 + 15; // range starting from 15 to 30

            while (!correctRange)
            {
                range_random = rand() % 5 + 1;
                if (range_random < rows_ || range_random < col_) // in case range value is greater than the dimensions
                {
                    z[i].zombieRange = range_random;
                    correctRange = true;
                }
            }
            map_[r_random][c_random] = z[i].zombieNo; // set rows and columns to each zombie
        }
    }
}

// set the game objects position
void Board::setRandom()
{
    string objects[] = {"h", "p", "r", "v", "^", "<", ">", " ", " ", "p", "b"};
    
    int noOfObjects = size(objects);
    int objNo = 0;

    // put random game objects into the vector array
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < col_; ++j)
        {
            if (map_[i][j].empty())
            {
                objNo = rand() % noOfObjects; // rand()obj in array string objects[]
                map_[i][j] = objects[objNo];
            }
        }
    }
}

// reset trail
void Board::reset()
{
    string objects[] = {"h", "p", "r", "v", "^", "<", ">", " ", "b"};
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

//check if alien wins
bool alienWin(int zombieCount, Zombie z[])
{
    bool alienWin = true;
    for (int i = 0; i < zombieCount && alienWin; i++)
    {
        alienWin = true;
        if (z[i].zombieStatus != "d")
        {
            alienWin = false;
        }
    }
    return alienWin;
}

void Board::displayPlayAgainMenu()
{
    string replayInput;
    bool continueRetryMenu = true;
    while (continueRetryMenu)
    {
        continueRetryMenu = false;
        cout << "Do you want to play again? (y/n): ";
        cin >> replayInput;
        if (replayInput == "y")
        {
            srand(time(NULL));
            int rows = abs((2 * rand()) % 16 + 1);
            int col = abs((2 * rand()) % 16 + 1);
            int zombieCount = abs(1 + (2 * rand()) % 10);
            displayGameContent(rows, col, zombieCount);
        }
        else if (replayInput == "n")
        {
            cout << "Bye bye.";
            exit(0);
        }
        else
        {
            cout << "Invalid input, please try again." << endl
                 << endl;
            continueRetryMenu = true;
        }
    }
}

// alien move
void Board::move(int zombieCount, bool &stopMove, string &command, bool &changeDirection, Alien &a, Zombie z[], string movement)
{
    int newAlienCol = 0;
    int newAlienRow = 0;
    string continueCommand = "";
    bool isBorder = true;
    if (movement == "left")
    {
        newAlienCol = a.alienCol - 1;
        newAlienRow = a.alienRow;
        continueCommand = "left"; // continue to move left
        if (a.alienCol > 0)
            isBorder = false;
    }
    else if (movement == "right")
    {
        newAlienCol = a.alienCol + 1;
        newAlienRow = a.alienRow;
        continueCommand = "right"; // continue to move right
        if (a.alienCol < col_ - 1)
            isBorder = false;
    }
    else if (movement == "down")
    {
        newAlienCol = a.alienCol;
        newAlienRow = a.alienRow + 1;
        continueCommand = "down";
        if (a.alienRow < rows_ - 1)
            isBorder = false;
    }
    else if (movement == "up")
    {
        newAlienCol = a.alienCol;
        newAlienRow = a.alienRow - 1;
        continueCommand = "up";
        if (a.alienRow > 0)
            isBorder = false;
    }

    if (!isBorder) // if isBorder == false
    {
        if (map_[newAlienRow][newAlienCol] == "r")
        {
            string objects[] = {"health pack", "pod", "nothing", "arrow"};
            int noOfObjects = size(objects);

            // rand() randomize the objects in the array
            int randObj = rand() % noOfObjects;
            cout << endl
                 << "Alien stumbles upon a rock." << endl;
            cout << "Alien discovers " << objects[randObj] << " beneath the rock." << endl;
            cout<<"Alien's turn ends. The trail is reset."<<endl;

            // if the randomize object is health pack
            if (objects[randObj] == "health pack")
            {
                // change the "r" object to "h"
                map_[newAlienRow][newAlienCol] = "h";
            }
            else if (objects[randObj] == "pod")
            {
                map_[newAlienRow][newAlienCol] = "p";
            }
            else if (objects[randObj] == "nothing")
            {
                map_[newAlienRow][newAlienCol] = " ";
            }
            else
            {
                string arrowObjects[] = {"^", "v", "<", ">"};
                int noOfArrowObjects = size(arrowObjects);
                int randObj = rand() % noOfArrowObjects;
                map_[newAlienRow][newAlienCol] = arrowObjects[randObj];
            }

            // stop move set to true to prevent from moving in same direction
            stopMove = true;

            a.alienAttack = 0;
        }
        else if (map_[newAlienRow][newAlienCol] == "p")
        {
            cout << endl
                 << "Alien finds a pod.";
            map_[a.alienRow][a.alienCol] = ".";

            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;

            //double distance[zombieCount];
            double tempDistance;
            int smallest = 0;
            double smallestDistance = 99999;
            bool hasAliveZombie = false;
            for (int k = 0; k < zombieCount; k++)
            {
                if (z[k].zombieStatus != "d") // check whether zombie has died
                {
                    hasAliveZombie = true;
                    int zombieR = z[k].zombieRow;
                    int zombieC = z[k].zombieCol;
                    tempDistance = sqrt((a.alienRow - zombieR) * (a.alienRow - zombieR) + (a.alienCol - zombieC) * (a.alienCol - zombieC));
                    if (tempDistance < smallestDistance){}
                    {
                        smallest = k; // find the smallest index of zombie from pod
                        smallestDistance=tempDistance;
                    } 
                }      
            }

            if (hasAliveZombie)
            {
                cout << endl
                     << "Zombie " << z[smallest].zombieNo << " receives a damage of 10." << endl;
                z[smallest].zombieLife = z[smallest].zombieLife - 10;

                if (z[smallest].zombieLife > 0)
                {
                    cout << "Zombie " << z[smallest].zombieNo << " is still alive."<<endl;
                }
                else
                {
                    z[smallest].zombieLife = 0;
                    cout << "Zombie " << z[smallest].zombieNo << " is defeated." << endl;

                    map_[z[smallest].zombieRow][z[smallest].zombieCol] = " ";
                    z[smallest].zombieAttack = 0;
                    z[smallest].zombieRange = 0;
                    z[smallest].zombieLife = 0;
                    z[smallest].zombieStatus = "d";

                    if (alienWin(zombieCount, z))
                    {
                        cout << endl
                             << "Congratulations! All zombies are defeated. You win!" << endl;
                        displayPlayAgainMenu();
                    }
                }
            }
        }
        else if (map_[newAlienRow][newAlienCol] == "b")
        {
            cout << endl
                 << "Alien discovers brain. Alien clears the brain to avoid Zombie getting cloned." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;

        }
        else if (map_[newAlienRow][newAlienCol] == "h")
        {
            if (a.alienLife != 100)
            {
                if(a.alienLife + 20 > 100){
                   int diff= 100 - a.alienLife;
                   a.alienLife= a.alienLife + diff;

                }else{
                 a.alienLife = a.alienLife + 20;
                }
               
                cout << endl
                     << "Alien finds a health pack." << endl;
                cout << "Alien's life is increased by 20." << endl;
            }
            else
            {
                cout << endl
                     << "Alien finds a health pack." << endl;
                cout << "Alien's life will not increase as is already at its maximum." << endl;
            }

            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
        }
        else if (map_[newAlienRow][newAlienCol] == " ")
        {
            cout << endl
                 << "Alien discovers nothing." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
        }
        else if (map_[newAlienRow][newAlienCol] == ".")
        {
            cout << endl
                 << "Alien discovers nothing." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
            changeDirection = true;
            stopMove = true;
            command = continueCommand;
        }
        else if (map_[newAlienRow][newAlienCol] == "^")
        {
            a.alienAttack = a.alienAttack + 20;
            cout << endl
                 << "Alien discovers an arrow." << endl;
            cout << "Alien receives an attack of 20." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
            changeDirection = true; // set changedirection flag to true to change direction
            stopMove = true;        // stop move=true prevent from moving in same direction
            command = "up"; // set the command to up
        }
        else if (map_[newAlienRow][newAlienCol] == "v")
        {
            a.alienAttack = a.alienAttack + 20;
            cout << endl
                 << "Alien discovers an arrow." << endl;
            cout << "Alien receives an attack of 20." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
            changeDirection = true;
            stopMove = true;
            command = "down";
        }
        else if (map_[newAlienRow][newAlienCol] == "<")
        {
            a.alienAttack = a.alienAttack + 20;
            cout << endl
                 << "Alien discovers an arrow." << endl;
            cout << "Alien receives an attack of 20." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
            changeDirection = true;
            stopMove = true;
            command = "left";
        }
        else if (map_[newAlienRow][newAlienCol] == ">")
        {
            a.alienAttack = a.alienAttack + 20;
            cout << endl
                 << "Alien discovers an arrow." << endl;
            cout << "Alien receives an attack of 20." << endl;
            map_[a.alienRow][a.alienCol] = ".";
            a.alienRow = newAlienRow;
            a.alienCol = newAlienCol;
            changeDirection = true;
            stopMove = true;
            command = "right";
        }
        else
        {
            cout << endl
                 << "Alien attacks zombie " << map_[newAlienRow][newAlienCol] << endl;
            bool matchZombie = false;
            for (int i = 0; i < zombieCount && !matchZombie; i++)
            {
                if (z[i].zombieNo == map_[newAlienRow][newAlienCol])
                {
                    cout << "Zombie " << map_[newAlienRow][newAlienCol] << " receives a damage of " << a.alienAttack << endl;
                    z[i].zombieLife = z[i].zombieLife - (a.alienAttack);
                    if (z[i].zombieLife > 0)
                    {
                        cout << "Zombie " << map_[newAlienRow][newAlienCol] << " is still alive." << endl;
                        cout << "Alien's turn ends. The trail is reset." << endl;
                        stopMove = true;
                        a.alienAttack = 0;
                    }
                    else
                    {
                        cout << "Zombie " << map_[newAlienRow][newAlienCol] << " is defeated." << endl;
                        map_[a.alienRow][a.alienCol] = ".";
                        a.alienRow = newAlienRow;
                        a.alienCol = newAlienCol;
                        z[i].zombieAttack = 0;
                        z[i].zombieRange = 0;
                        z[i].zombieLife = 0;
                        z[i].zombieStatus = "d";

                        if (alienWin(zombieCount, z))
                        {
                            cout << endl
                                 << "Congratulations! All zombies are defeated. You win!" << endl;
                            displayPlayAgainMenu();
                        }
                    }
                    matchZombie = true;
                }
            }

            if (alienWin(zombieCount, z))
            {
                cout << "Congratulations! All zombies are defeated. You win!" << endl;
                displayPlayAgainMenu();
            }
        }
    }
    else
    {
        cout <<endl<< "Alien hits a border." << endl;
        cout << "Alien's turn ends. The trail is reset." << endl;
        // stop moving when hit border
        stopMove = true;
        a.alienAttack = 0;
        
    }
}

// users input command
void Board::command(int &zombieCount, bool &quitFlag, Zombie (&z)[], Alien &a )
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
        if (command == "left" || command == "right" || command == "down" || command == "up")
        {
            while (!stopMove)
            {
                move(zombieCount, stopMove, command, changeDirection, a, z, command);
                setAlien(a);

                cout << endl
                     << "Press any key to continue...." << endl;
                getch();

                if (stopMove == true && changeDirection == false)
                {
                    reset(); // reset the trail
                }

                displayGameHeader();
                displayAlienInfo(a);
                displayZombieInfo(zombieCount, z);
            }
        }
        else if (command == "arrow")
        {
            int ucol, urow;
            string uarrow;

            cout << "Enter Row => ";
            cin >> urow;
            cout << "Enter Column => ";
            cin >> ucol;
            cout << "Enter new arrow => ";
            cin >> uarrow;

            int x, y;
            x = (urow - rows_) * -1;
            y = ucol - 1;
            string oriarrow = map_[x][y];
            if (oriarrow != "<" && oriarrow != ">" && oriarrow != "v" && oriarrow != "^")
            {
                cout << "The Row " << urow << " and Column " << ucol << " is not an arrow" << endl<< "Please try again..." << endl;
            }
            else
            {
                if (uarrow == "right")
                {
                    map_[x][y] = ">";
                    cout << endl
                         << "Updated Successfully" << endl;
                    cout << "Arrow " << oriarrow << " is switched to >";
                }
                else if (uarrow == "left")
                {
                    map_[x][y] = "<";
                    cout << endl
                         << "Updated Successfully" << endl;
                    cout << "Arrow " << oriarrow << " is switched to <";
                }
                else if (uarrow == "up")
                {
                    map_[x][y] = "^";
                    cout << endl
                         << "Updated Successfully" << endl;
                    cout << "Arrow " << oriarrow << " is switched to ^";
                }
                else if (uarrow == "down")
                {
                    map_[x][y] = "v";
                    cout << endl
                         << "Updated Successfully" << endl;
                    cout << "Arrow " << oriarrow << " is switched to v";
                }
                else
                {
                    cout << "Invalid arrow, please try again...";
                }
            }
                cout << endl
                     << "Press any key to continue...." << endl;
                getch();
            displayGameHeader();
            displayAlienInfo(a);
            displayZombieInfo(zombieCount, z);

            this->command(zombieCount, quitFlag, z, a );
        }
        else if (command == "quit")
        {
            string ans;
            cout << "Do you sure you want to quit this game? (y/n) : ";
            cin >> ans;
            if (ans == "y")
            {
                cout << "ByeBye" ;
                quitFlag = true;
                changeDirection = false;
                stopMove = true;
                exit(0);
            }
            else if (ans == "n")
            {
                displayGameHeader();
                displayAlienInfo(a);
                displayZombieInfo(zombieCount, z);
                this->command(zombieCount, quitFlag, z, a );
            }
        }
        else if (command == "save")
        {
            save(*this, a, z, zombieCount);

            displayGameHeader();
            displayAlienInfo(a);
            displayZombieInfo(zombieCount, z);

            this->command(zombieCount, quitFlag, z, a );
        }
        else if (command == "load")
        {
            char ans;
            cout << "Do you want to save the current game? (y/n) : ";
            cin >> ans;
            if (ans == 'y')
            {
                save(*this, a, z, zombieCount);
                load(*this, a, z, zombieCount);
            }
            else if (ans == 'n')
            {
                load(*this, a, z, zombieCount);
            }
            displayGameHeader();
            displayAlienInfo(a);
            displayZombieInfo(zombieCount, z);

            this->command(zombieCount, quitFlag, z, a );
        }
        else if (command == "help")
        {
            cout << endl;
            cout << "up      -Alien to move up." << endl;
            cout << "down    -Alien to move down." << endl;
            cout << "left    -Alien to move left." << endl;
            cout << "right   -Alien to move right." << endl;
            cout << "arrow   -Switch the direction of an arrow object in the game board." << endl;
            cout << "help    -Display the user commands." << endl;
            cout << "save    -Save the current game." << endl;
            cout << "load    -Load the game." << endl;
            cout << "quit    -Quit the game." << endl;

            displayGameHeader();
            displayAlienInfo(a);
            displayZombieInfo(zombieCount, z);

            this->command(zombieCount, quitFlag, z, a );
        }
        else
        {
            cout << "Invalid command." << endl
                 << "Press any key to continue...." << endl;
            getch();

            displayGameHeader();
            displayAlienInfo(a);
            displayZombieInfo(zombieCount, z);

            this->command(zombieCount, quitFlag, z, a );
        }
    }
}

// main
int main()
{
    cout << "Alien Vs Zombie Game" << endl;
    cout << "Let's Get Started!" << endl;

    srand(time(NULL));
    int rows = abs((2 * rand()) % 16 + 1);
    int col = abs((2 * rand()) % 16 + 1);
    int zombieCount = abs(1 + (2 * rand()) % 10); 

    Board b(col, rows);
    b.displayGameContent(rows, col, zombieCount);
}
