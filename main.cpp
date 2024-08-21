#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;

#define MAX_SNAKE_LENGTH 1000

const char MOVE_UP = 'U';
const char MOVE_DOWN = 'D';
const char MOVE_LEFT = 'L';
const char MOVE_RIGHT = 'R';

int screenWidth, screenHeight;

void initializeScreen()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    screenHeight = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;
    screenWidth = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
}

struct Coordinate{
    int x;
    int y;
    Coordinate(){}
    Coordinate(int xVal, int yVal) : x(xVal), y(yVal) {}
};

class SnakeGame{
    int snakeLength;
    char currentDirection;
public:
    Coordinate snakeBody[MAX_SNAKE_LENGTH];

    SnakeGame(int startX, int startY)
    {
        snakeLength = 1;
        snakeBody[0] = Coordinate(startX, startY);
        currentDirection = MOVE_RIGHT;
    }

    int getSnakeLength(){
        return snakeLength;
    }

    void updateDirection(char newDirection){
        if(newDirection == MOVE_UP && currentDirection != MOVE_DOWN)
            currentDirection = newDirection;
        else if(newDirection == MOVE_DOWN && currentDirection != MOVE_UP)
            currentDirection = newDirection;
        else if(newDirection == MOVE_LEFT && currentDirection != MOVE_RIGHT)
            currentDirection = newDirection;
        else if(newDirection == MOVE_RIGHT && currentDirection != MOVE_LEFT)
            currentDirection = newDirection;
    }

    bool advanceSnake(Coordinate foodPosition){

        for(int i = snakeLength - 1; i > 0; i--)
            snakeBody[i] = snakeBody[i-1];

        switch(currentDirection)
        {
            case MOVE_UP:
                snakeBody[0].y -= 1;
                break;
            case MOVE_DOWN:
                snakeBody[0].y += 1;
                break;
            case MOVE_RIGHT:
                snakeBody[0].x += 1;
                break;
            case MOVE_LEFT:
                snakeBody[0].x -= 1;
                break;
        }

        for(int i = 1; i < snakeLength; i++)
            if(snakeBody[0].x == snakeBody[i].x && snakeBody[0].y == snakeBody[i].y)
                return false;

        if(foodPosition.x == snakeBody[0].x && foodPosition.y == snakeBody[0].y)
        {
            snakeBody[snakeLength] = Coordinate(snakeBody[snakeLength-1].x, snakeBody[snakeLength-1].y);
            snakeLength++;
        }

        return true;
    }
};

class GameBoard{
    SnakeGame *snake;
    const char SNAKE_SYMBOL = 'O';
    Coordinate foodPosition;
    const char FOOD_SYMBOL = 'x';
    int gameScore;

public:
    GameBoard(){
        placeFood();
        snake = new SnakeGame(10, 10);
        gameScore = 0;
    }

    ~GameBoard(){
        delete snake;
    }

    int getGameScore(){
        return gameScore;
    }

    void placeFood(){
        int xPos = rand() % screenWidth;
        int yPos = rand() % screenHeight;
        foodPosition = Coordinate(xPos, yPos);
    }

    void showScore(){
        setCursorPosition(screenWidth / 2, 0);
        cout << "Current Score: " << gameScore;
    }

    void setCursorPosition(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void render(){
        system("cls");
        for(int i = 0; i < snake->getSnakeLength(); i++)
        {
            setCursorPosition(snake->snakeBody[i].x, snake->snakeBody[i].y);
            cout << SNAKE_SYMBOL;
        }

        setCursorPosition(foodPosition.x, foodPosition.y);
        cout << FOOD_SYMBOL;

        showScore();
    }

    bool updateGame(){
        bool snakeAlive = snake->advanceSnake(foodPosition);
        if(!snakeAlive)
            return false;

        if(foodPosition.x == snake->snakeBody[0].x && foodPosition.y == snake->snakeBody[0].y)
        {
            gameScore++;
            placeFood();
        }
        return true;
    }

    void handleInput(){
        if(kbhit())
        {
            int keyPressed = getch();
            if(keyPressed == 'w' || keyPressed == 'W')
                snake->updateDirection(MOVE_UP);
            else if(keyPressed == 'a' || keyPressed == 'A')
                snake->updateDirection(MOVE_LEFT);
            else if(keyPressed == 's' || keyPressed == 'S')
                snake->updateDirection(MOVE_DOWN);
            else if(keyPressed == 'd' || keyPressed == 'D')
                snake->updateDirection(MOVE_RIGHT);
        }
    }
};

int main(){
    srand(time(0));
    initializeScreen();
    GameBoard *gameBoard = new GameBoard();

    while(gameBoard->updateGame())
    {
        gameBoard->handleInput();
        gameBoard->render();
        Sleep(100);
    }

    cout << "Game over" << endl;
    cout << "Final score: " << gameBoard->getGameScore();

    delete gameBoard;
    return 0;
}
