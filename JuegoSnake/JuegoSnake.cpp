/*
Programa: Juego del Snake
Autor: Sergio Sanchez Iglesias
Fecha: 7/10/2021
*/

#include "JuegoSnake.h"


int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
    }

    return 0;
}

void setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
    system("clear");
    for(int i = 0; i < width+2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j==0)
            {
                std::cout << "#";
            }

            if(i == y && j == x)
            {
                std::cout << "O";
            }else if(i == fruitY && j == fruitX){
                std::cout << "F";
            }else{
                bool print = false;
                for(int k = 0; k < nTail; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    std::cout << " ";
            }

            if(j==width-1)
            {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < width+2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "Score = " << score << std::endl;

}

void input()
{
    /*IMPORTANTE MIRAR UNA FUNCIONALIDAD DE _kbhit() y getch()
    para realizarlo correctamente*/
    char c;
    switch(c=getchar())
    {
        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir =  RIGHT;
            break;
        
        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'x':
            gameOver = true;
            break;
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if(x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
    }

    for(int i = 0; i < nTail; i++)
    {
       if(tailX[i] == x && tailY[i] == y) 
       {
           gameOver = true;
       }
    }

    if(x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}


