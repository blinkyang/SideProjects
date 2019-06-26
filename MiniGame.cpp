#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void setup();
void input();
void draw();
void logic();

bool gameOver = false;
char cont = 'y';
bool conti;

const int width = 40;
const int height = 40;
int numObj = 10;
int score = 0;
int lvl = 1;

int headX, headY, foodX, foodY;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int objX[100];
int objY[100];
bool checked;


int main()
{
    do
    {
        setup();
        while(!gameOver)
        {
            draw();
            input();
            logic();
            Sleep(50);
        }
        cout << "Continue? (y/n)" << endl;
        do
        {
            cin >> cont;
            if (cont == 'y' || cont == 'n')
            {
                conti = true;
            }
        } while (conti != true);



    } while (cont != 'n');
    cout << "Thanks for Playing!!" << endl;

    return 0;
}

void setup()
{
    headX = width/2;
    headY = height/2;
    foodX = rand() % (width-1) + 1;
    foodY = rand() % height;

    for (int i=0; i < numObj; i++)
    {
        do
        {
        objX[i] = rand() % (width-1) +1;
        objY[i] = rand() % height;
        } while(foodX == objX[i] && foodY == objY[i]);
    }

    dir = STOP;
    gameOver = false;
    score = 0;
    lvl = 1;
    numObj = 10;
    cont = 'y';
    conti = false;


}

void draw()
{
    system("cls");
    for (int i = 0; i < width; i++)
        cout << '#';

    cout << endl;


    for (int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            checked = false;
            for (int k = 0; k < numObj; k++)
            {
                if (x == objX[k] && y == objY[k])
                {
                    cout << 'X';
                    checked = true;
                }
            }

            if (x == headX && y == headY && checked != true)
            {
                    cout << 'O';
            }
            else if (x == foodX && y == foodY && checked != true)
            {
                    cout << '~';
            }
            else if (x == 0 || x == width-1 && checked != true)
            {
                cout << '#';
            }
            else if (checked != true)
            {
                cout << " ";
            }
        }
        cout << endl;
    }



    for (int i = 0; i < width; i++)
        { cout << '#'; }

        cout << endl;

        cout << "Level: " << lvl << "/10\t\t\t" << "Score: " << score << endl;
}

void input()
{
    if (_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 'q':
            gameOver = true;
            break;
        }
    }


}


void logic()
{
    switch(dir)
    {
    case LEFT:
        headX--;
        break;

    case RIGHT:
        headX++;
        break;

    case DOWN:
        headY++;
        break;

    case UP:
        headY--;
        break;

    default:
        break;
    }

    for (int k = 0; k < numObj; k++)
    {
        if (headX == objX[k] && headY == objY[k])
        {
            gameOver = true;
        }
    }

    if (headX >= width || headX <= 0 || headY > height || headY < 0)
    {
        gameOver = true;
    }

    if (headX == foodX && headY == foodY)
    {
        score += 1000;
        lvl++;
        foodX = rand() % (width-1) + 1;
        foodY = rand() % height;

        if (numObj != 100)
        {
            numObj += 10;
        }
        else
        {
            gameOver = true;
            cout << "You've Won the game!!" << endl;
        }

        for (int i=0; i < numObj; i++)
        {
            do
            {
            objX[i] = rand() % (width-1) +1;
            objY[i] = rand() % height;
            } while(foodX == objX[i] && foodY == objY[i]);
        }

    }
    if (score > 0)
    {
        score--;
    }



}
