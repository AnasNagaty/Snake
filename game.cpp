#include <GL/gl.h>
#include <GL/glut.h>
#include <ctime>
#include <unistd.h>
#include "game.h"
#define MAX 20

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define W 1
#define S -1
#define D 2
#define A -2
//------------------------------  Start going in the right direction  ---------------------------------
short sDirection = RIGHT;
short sDirection2 = D;

int snake_length = 5;
//int snake_length2 = 5;

int foodX, foodY;
bool food = true;
extern bool GameOver;

extern int score1;
extern int score2;

int gridX, gridY;

//------------------------------  Position of players  ---------------------------------
int posX[20] = {20,20,20,20,20}, posY[20] = {20,19,18,17,16};
int pos2X[20] = {18,18,18,18,18}, pos2Y[20] = {18,17,16,15,14};
float shX=30 , shY=30;

//------------------------------  BackGround Grid  ---------------------------------
void initGrid(int x, int y)
{
    gridX = x;
    gridY = y;
}

void unit(int,int);

//------------------------------  Random function for food  ---------------------------------
void random(int &x, int &y)
{
    int _maxX = gridX-2;
    int _maxY = gridY-2;
    int _min = 1;
    srand(time(NULL));
    x = _min + rand() % (_maxX - _min);
    y = _min + rand() % (_maxY - _min);
}


void drawGrid()
{
    for(int x=0 ; x<gridX ; x++)
        {
        for(int y=0 ; y<gridY ; y++)
        {
            unit(x,y);
        }
    }
}

//------------------------------  1x1 grid square  ---------------------------------
void unit(int x, int y)
{
    if(x==0 || y==0 || x==gridX-1 || y==gridY-2)
    {
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }



    glBegin(GL_POLYGON);
        glVertex3f(x,y,1);
        glVertex3f(x+1,y,1);
        glVertex3f(x+1,y+1,1);
        glVertex3f(x,y+1,1);
    glEnd();
}

//------------------------------  Food Spawning randomly  ---------------------------------
void drawFood()
{
    if(food)
        random(foodX,foodY);
    food = false;
    glColor3f(1.0,0.0,0.0);
    glRectf(foodX,foodY,foodX+1,foodY+1);

}

//------------------------------  First snake  ---------------------------------
void drawSnake()
{
    for(int i=snake_length-1; i>0 ; i--)
    {
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }
    if(sDirection==UP)
        posY[0]++;
    else if (sDirection==DOWN)
        posY[0]--;
    else if (sDirection==RIGHT)
        posX[0]++;
    else if (sDirection==LEFT)
        posX[0]--;

    for(int i=0 ; i<snake_length; i++)
    {
        if(i == 0)
            glColor3f(0.0,1.0,0.0);
        else
            glColor3f(0.0,0.0,1.0);
    glRectd(posX[i], posY[i], posX[i]+1, posY[i]+1);
    }

    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-2)
        GameOver=true;

    if(posX[0]==foodX && posY[0]==foodY)
    {
        score1++;
        snake_length++;
        if(snake_length>MAX)
            snake_length==MAX;
        food=true;
    }
}

//------------------------------  Second snake  ---------------------------------
void drawSnake2()
{
    for(int i=snake_length-1; i>0 ; i--)
    {
        pos2X[i] = pos2X[i-1];
        pos2Y[i] = pos2Y[i-1];
    }

    if(sDirection2==W)
        pos2Y[0]++;
    else if (sDirection2==S)
        pos2Y[0]--;
    else if (sDirection2==D)
        pos2X[0]++;
    else if (sDirection2==A)
        pos2X[0]--;

    for(int i=0 ; i<snake_length; i++)
    {
    if(i == 0)
            glColor3f(1.0,1.0,0.0);
        else
            glColor3f(1.0,0.0,1.0);
    glRectd(pos2X[i], pos2Y[i], pos2X[i]+1, pos2Y[i]+1);
    }

    if(pos2X[0]==0 || pos2X[0]==gridX-1 || pos2Y[0]==0 || pos2Y[0]==gridY-2)
        GameOver=true;

    if(pos2X[0]==foodX && pos2Y[0]==foodY)
    {
        score1++;
        snake_length++;
        if(snake_length>MAX)
            snake_length==MAX;
        food=true;
    }
}

//------------------------------  Ant  ---------------------------------
void shereer(){
    //repeat if tofaha loc change
    //check tofaha location
    //move horizontal till y = tofaha's y
    //move vertical till x = tofaha's x
    glColor3f(0.45,0.19,0.6);
    glRectd(shX, shY, shX+1, shY+1);

        if(shX - foodX > 0 ){
            shX-=0.5;
        }else if (shX - foodX < 0) {
            shX+=0.5;
        }


        if(shY - foodY > 0){
            shY-=0.5;
        }else if(shY - foodY < 0){
            shY+=0.5;
        }

    if(shX==foodX && shY==foodY)
    {
        score2++;
        food=true;
    }

}
