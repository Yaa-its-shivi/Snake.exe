// required header file
#include <conio.h> //provides functions _kbhit() for keyboard  and _getch() reads the key
#include <iostream> //handles input/output streams like cin and cout
#include <windows.h> //Windows-specific functions like Sleep() to delay the game loop and system("cls") to clear the screen.
#include<deque> 
using namespace std;

// height and width of the boundary Board size: 80 cols X 20 rows
const int width = 60; 
const int height = 20;
const char HEAD_SYMBOL='@';
const char FOOD_SYMBOL='*';
const char TAIL_SYMBOL='+';
const char WALL_HORIZONTAL='=';
const char WALL_VERTICAL='|';

// Snake head coordinates of snake (x-axis, y-axis)
int headX, headY;
// Food coordinates
int foodX, foodY;
// variable to store the score of he player
int score=0;
//variable to game
bool gameOver=false;
// variable to store the length of the sanke's tail
deque<pair<int,int>> tail;
// for storing snake's moving snakesDirection
enum Direction { STOP, LEFT, RIGHT, UP, DOWN }; // Defines possible movement directions for the snake.
// snakesDirection variable
Direction dir; // current movement direction
// boolean variable for checking game is over or not
bool isGameOver; //keeps track of whether the game is still running.

// Function to initialize game variables
void initGame()
{
    gameOver = false;
    dir = STOP; // snake is not moving initally stop
    headX = width / 2; // snake starts in center
    headY = height / 2;
    foodX = rand() % width; // food appears at random location
    foodY = rand() % height;
    score = 0; //initialy score is zero
    tail.clear();
}

// Function for creating the game board & rendering
void drawFrame(string playerName) // Renders the entire game screen based on snake/food/tail positions.
{
    system("cls"); // Clear the console screen

    // Creating top walls with '-'
    for (int i = 0; i < width + 2; i++)
        cout << WALL_HORIZONTAL;
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Creating side walls with '|'
            if (j == 0 || j == width)
                cout << WALL_VERTICAL;
            // Creating snake's head with 'O'
            if (i == headY && j == headX)
                cout << HEAD_SYMBOL;
            // Creating the sanke's food with '#'
            else if (i == foodY && j == foodX)
                cout << FOOD_SYMBOL;
            // Creating snake's head with 'O'
            else {
                bool isTail = false;
                for (auto segment : tail) {
                    if (segment.first == j
                        && segment.second == i) {
                        cout <<TAIL_SYMBOL;
                        isTail = true;
                    }
                }
                if (!isTail)
                    cout << ' ';
            }
        }
        cout << endl;
    }

    // Creating bottom walls with '-'
    for (int i = 0; i < width + 2; i++)
        cout << WALL_HORIZONTAL;
    cout << endl;

    // Display player's score
    cout << "\nPlayer: " << playerName << " | Score: " << score
         << endl;
}

// Function for updating the game state
void updateGame()
{
    tail.push_front({headX,headY});
    if(tail.size()>score) tail.pop_back();
    

    

    switch (dir) {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default: break;
    }

    // Checks for snake's collision with the wall (|)
    if (headX >= width || headX < 0 || headY >= height || headY < 0)
        gameOver = true;

    // Checks for collision with the tail (o)
    for (auto segment : tail){
        if(segment.first==headX&&segment.second==headY)
            gameOver = true;
    }

    // Checks for snake's collision with the food (#)
    if (headX == foodX && headY == foodY) {
        score += 1;
        foodX = rand() % width;
        foodY = rand() % height;
        
    }
}

// Function to set the game difficulty level
int chooseSpeed()
{
    int level;
    cout << "Select Difficulty Level:\n1. Slow\n2. Normal\n3. Fast\n Enter choice: ";
    cin >> level;
    switch (level) {
    case '1':
        return 150;
        
    case '3':
        return 50;
        
    default:
       return 100;
    }
}

// Function to handle user UserInput
void handleInput()
{
    // Checks if a key is pressed or not
    if (_kbhit()) {
        // Getting the pressed key
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'e':
            gameOver = true;
            break;
        }
    }
}

// Main function / game looping function
int main()
{
    string playerName;
    cout << "Welcome to Console Snake Game!\nEnter your name: ";
    cin >> playerName;
    int speed = chooseSpeed();

    initGame();
    while (!gameOver) {
        drawFrame(playerName);
        handleInput();
        updateGame();
        // creating a delay for according to the chosen
        // difficulty
        Sleep(speed);
    }

    cout << "\nGame Over, " << playerName << "! Final Score: " << score << endl;
    system("pause");
    return 0;
}