#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <mmsystem.h>
#include <windows.h>

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define W 1
#define S -1
#define D 2
#define A -2

#include "game.h"

#define COLUMNS 50
#define ROW 35
#define FPS 5

const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;

bool GameOver=false;

int start=0;
int score1 = 0;
int score2 = 0;

extern short sDirection;
extern short sDirection2;

void timer(int);
void timer2(int);

void display();
void reshape(int w,int h);
void keyboard(unsigned char, int , int );

float zRotated = 0.0;
float t = 0.0;

void drawSnake();
void drawSnake2();
void drawFood();
void shereer();


void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    initGrid(COLUMNS,ROW);
    PlaySound("E:\\Others\\s4-league-soundtrack-s4-league-in-the-building.wav",NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
}

void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

//------------------------------  reshapeFunc  ---------------------------------

void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROW,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}



void fristDesign(){
    //gluPerspective (40.0, 800 / 700, 0.5, 20.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(0.0f, 0.0f, -15.0f);

glPushMatrix();
glColor3f(1,0,0);
glTranslatef(0,-4,0-2);
glutSolidSphere(3,10,10);
glPopMatrix();
    glColor3f(1,1,0);
    glPushMatrix();
    glTranslated(20,20,0);
    glRotated(60,0,0,1);
    glutSolidTorus(0.2,0.8,15,15);
    glPopMatrix();

    glPushMatrix();
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
        //glRotated(30,1,0,0);
        glRotated(a,0,0,1);
    glBegin(GL_QUADS);
   // Front face
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 40.0f, 25.0f, 15.0f);
      glVertex3f(10.0f, 25.0f, 15.0f);
      glVertex3f(10.0f, 15.0f, 15.0f);
      glVertex3f( 40.0f, 15.0f, 15.0f);

      // Right face
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(40.0f,  25.0f, -15.0f);
      glVertex3f(40.0f,  25.0f, 15.0f);
      glVertex3f(40.0f, 15.0f, 15.0f);
      glVertex3f(40.0f, 15.0f, -15.0f);

      // Back face
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 40.0f, 15.0f, -15.0f);
      glVertex3f(10.0f, 15.0f, -15.0f);
      glVertex3f(10.0f,  25.0f, -15.0f);
      glVertex3f( 40.0f,  25.0f, -15.0f);

      // Left face
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(10.0f,  25.0f,  15.0f);
      glVertex3f(10.0f,  25.0f, -15.0f);
      glVertex3f(10.0f, 15.0f, -15.0f);
      glVertex3f(10.0f, 15.0f,  15.0f);
    glEnd();
    glPopMatrix();


    glBegin(GL_QUADS);
   // Front face
      glColor3f(0.0f, 0.0f, 1.0f);     // Red
      glVertex3f( 40.0f, 25.0f, 15.0f);
      glVertex3f(10.0f, 25.0f, 15.0f);
      glVertex3f(10.0f, 15.0f, 15.0f);
      glVertex3f( 40.0f, 15.0f, 15.0f);

      // Right face
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(40.0f,  25.0f, -15.0f);
      glVertex3f(40.0f,  25.0f, 15.0f);
      glVertex3f(40.0f, 15.0f, 15.0f);
      glVertex3f(40.0f, 15.0f, -15.0f);

      // Back face
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 40.0f, 15.0f, -15.0f);
      glVertex3f(10.0f, 15.0f, -15.0f);
      glVertex3f(10.0f,  25.0f, -15.0f);
      glVertex3f( 40.0f,  25.0f, -15.0f);

      // Left face
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(10.0f,  25.0f,  15.0f);
      glVertex3f(10.0f,  25.0f, -15.0f);
      glVertex3f(10.0f, 15.0f, -15.0f);
      glVertex3f(10.0f, 15.0f,  15.0f);
    glEnd();

glPushMatrix();
glTranslated(10,20,-15);
glRotated(zRotated,1,0,0);
glBegin(GL_TRIANGLES);
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f , 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f , -1.0f , 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f , -1.0f  , 1.0f);

      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f , 1.0f , 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f , -1.0f , 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f , -1.0f , -1.0f);

      // back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f  , 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f , -1.0f  , -1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f , -1.0f , -1.0f);

      // left
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f , 1.0f , 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f , -1.0f , -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f , -1.0f, 1.0f);

   glEnd();
   glPopMatrix();
glTranslatef(0.0f, 0.0f, 15.0f);



        glColor3f(1.000, 1.000, 0.000);
        renderBitmapString(21,23,(void *)font1," Snake Game ");

        glColor3f(0.000, 1.000, 0.000);
        renderBitmapString(20,21,(void *)font2,"Press SPACE to START");

        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(12,12,(void *)font3,"PLAYER 1 CONTROLS");
        renderBitmapString(12,10,(void *)font3,"8 4 5 6");

        renderBitmapString(30,12,(void *)font3,"PLAYER 2 CONTROLS");
        renderBitmapString(30,10,(void *)font3,"W A S D");

}

void startGame(){
        drawGrid();
        drawSnake();
        drawSnake2();
        drawFood();
        shereer();
}


void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(start==1){
        startGame();
    }

    else{
        fristDesign();
    }

    glLoadIdentity();

    glutSwapBuffers();

    //------------------------------  GameOver  ---------------------------------
    if(GameOver)
    {
        char _score1[10];
        char _score2[10];
        itoa(score1,_score1,10);
        itoa(score2,_score2,10);

        char text[50] = " Players Score: ";
        strcat(text,_score1);

        char text2[50] = " AI Score: ";
        strcat(text2,_score2);

        strcat(text,text2);

        MessageBox(NULL, text, "GAME OVER",0);
        exit(0);
    }
}


//--------------------------------  idleFunc  ----------------------------------

void idleFunc (void)
{
    zRotated += 0.01;
    glutPostRedisplay();
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 650);
    glutInitWindowPosition(300, 000);
    glutCreateWindow("17100730 - 17101265 - 17101719");

    glutDisplayFunc (display);

    glutReshapeFunc (reshapeFunc);
    glOrtho(0,100,0,100,-1,1);
    glutTimerFunc(0,timer,0);
    glutTimerFunc(0,timer2,0);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();
    glutIdleFunc(idleFunc);


    return 0;
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}

void timer2(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer2,0);
    t+=10;
}



//------------------------------  input  ---------------------------------
void keyboard(unsigned char key, int, int){

    switch(key){
      case '8':
        if(sDirection != DOWN)
            sDirection = UP;
            break;

      case '5':
        if(sDirection != UP)
            sDirection = DOWN;
            break;

      case '6':
        if(sDirection != LEFT)
            sDirection = RIGHT;
            break;

      case '4':
        if(sDirection != RIGHT)
            sDirection = LEFT;
            break;

      case 'w':
        if(sDirection2 != S)
            sDirection2 = W;
            break;

      case 's':
        if(sDirection2 != W)
            sDirection2 = S;
            break;

      case 'd':
        if(sDirection2 != A)
            sDirection2 = D;
            break;

      case 'a':
        if(sDirection2 != D)
            sDirection2 = A;
            break;

      case ' ':
            if(start==0)
                start = 1;

    }
}
