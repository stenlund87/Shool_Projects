#include <Adafruit_GFX.h>
#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include "myasset.h"
#include "ghost.h"
#include "Variables.h"

int lives = 3;
int frame = 0;
int anim = 0;

int absX = 0;
int absY = 0;

int pX = STARTX;
int pY = STARTY;

int pSquareX = ((STARTX - OFFSET_X)*0.125)+0.5;
int pSquareY = (((STARTY - OFFSET_Y)*0.125))+0.5;

int dX = 0;
int dY = 0;

int animationHandle = 2;
int animationLimit = 3;

int resetFrame = 0;

Ghost blinky = Ghost(OFFSET_X+13*8, 11*8+OFFSET_Y, BLINKY_HANDLE, BLINKYID);
Ghost clyde = Ghost(OFFSET_X+15*8, 14*8+OFFSET_Y, CLYDE_HANDLE, CLYDEID);
Ghost inky = Ghost(OFFSET_X+11*8, 14*8+OFFSET_Y, INKY_HANDLE, INKYID);
Ghost pinky = Ghost(OFFSET_X+13*8, 14*8+OFFSET_Y, PINKY_HANDLE, PINKYID);

void setup()
{  
  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN,HIGH);
  Serial.begin(115200);
  
  GD.begin();
  LOAD_ASSETS();
  GD.BitmapHandle(PM_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 256, 256);

  //Load handles for pacman
  GD.BitmapHandle(PACMAN_LEFT_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 13, 13);
  GD.BitmapHandle(PACMAN_RIGHT_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 13, 13);
  GD.BitmapHandle(PACMAN_UP_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 13, 13);
  GD.BitmapHandle(PACMAN_DOWN_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 13, 13);
  GD.BitmapHandle(PACMAN_DEATH15X13_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 15, 13);

  //Load handles for the ghosts
  GD.BitmapHandle(BLINKY_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 14, 14);
  GD.BitmapHandle(CLYDE_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 14, 14);
  GD.BitmapHandle(INKY_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 14, 14);
  GD.BitmapHandle(PINKY_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 14, 14);
  GD.BitmapHandle(EYES_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 14, 14);
  GD.BitmapHandle(GHOST_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 14, 14);  
  
  CountPills();
  blinky.pillLimit = numPills;
  clyde.pillLimit = numPills*0.3;
  inky.pillLimit = numPills-30;
  pinky.pillLimit = numPills;
}

void loop()
{

  GD.Clear();

  GD.Begin(BITMAPS);
  GD.Vertex2ii(112 , 8, PM_HANDLE);
  GD.Vertex2ii(pX-8, pY-8, animationHandle,anim);
  DrawPills();
  if(!gameOver && lives >0)
  {
    ReadInput();

    MovePacman();  
    EatPills();
    pSquareX = ((pX - OFFSET_X)*0.125)+0.5;
    pSquareY = (pY - OFFSET_Y)*0.125+0.5;

    if(pSquareX == 0 && pSquareY == 14 && dX == -1)
    {
      pSquareX = 27;
      pSquareY = 14;
      pX = (27*8)+OFFSET_X;
      pY = (14*8)+OFFSET_Y;
    }
    else if(pSquareX == 27 && pSquareY == 14 && dX == 1)
    {
      pSquareX = 0;
      pSquareY = 14;
      pX = OFFSET_X;
      pY = (14*8)+OFFSET_Y;
    }
    
    //Render the ghosts
    blinky.Update(pSquareX, pSquareY, blinky);
    clyde.Update(pSquareX, pSquareY, clyde);
    inky.Update(pSquareX+dX*2,pSquareY +dY*2, blinky);
    pinky.Update(pSquareX+dX*4,pSquareY +dY*4, pinky);
    
    //Check if one of the ghosts are at the same tile as Pacman
    blinky.CheckGameOver(pSquareX, pSquareY);
    clyde.CheckGameOver(pSquareX, pSquareY);
    inky.CheckGameOver(pSquareX, pSquareY);
    pinky.CheckGameOver(pSquareX, pSquareY);
  }
  else
  {
    animationHandle = PACMAN_DEATH15X13_HANDLE;
    animationLimit = 12;  
  }
  if(lives > 0)
  {
    AnimatePacman();
  }
  else
  {
    GD.cmd_text(240, 136, 25, OPT_CENTER, "GAME OVER!");
  }
  

  GD.cmd_text(380, 50, 18, 0, "Score: ");
  GD.cmd_number(380, 80, 18, 0, highscore );
  frame++;
  
  if(numPills == 0)
  {
    GD.cmd_text(240, 100, 25, OPT_CENTER, "LEVEL CLEARED!");
    GD.cmd_text(240, 136, 25, OPT_CENTER, "Score: ");
    GD.cmd_number(240, 176, 25, OPT_CENTER, highscore );

    if(resetFrame > 1000)
    {
      ResetGame();
    }
    
    resetFrame++; 
  }
  for(int i = 0; i < lives-1; i++)
  {
    GD.Vertex2ii(360+i*14, 200, PACMAN_LEFT_HANDLE,0);
  }
  
  GD.swap();
}

void MovePacman()
{
  if(M[pSquareY + dY][pSquareX + dX] != 'x')
  {
    pX += dX;
    pY += dY;
  }
  else if(absX >= 1 || absY >=1)
  {
    pX += dX;
    pY += dY;
  }
}

void AnimatePacman()
{
  if(frame > ANIMATIONTIME)
  {
    anim++;
    frame = 0;
    if(anim == animationLimit && !gameOver) anim = 0;
    else if( anim == animationLimit && gameOver)  ResetPositions();

  }
}

void ReadInput()
{
  int x = analogRead(X_PIN);
  delay(15);
  int y = analogRead(Y_PIN);

  int tempX = (pSquareX*8 + OFFSET_X);
  int tempY = (pSquareY*8 + OFFSET_Y);
  
  absX = abs(tempX - pX);
  absY = abs(tempY - pY);
  
  if(x > 520 && x>y && absY < 1 && M[pSquareY][pSquareX +1] != 'x')
  {
    dX = 1;
    dY = 0;
    animationHandle = PACMAN_RIGHT_HANDLE;
  }
  else if(x < 500 && x < y && absY < 1 && M[pSquareY][pSquareX -1] != 'x')
  {
    dX = -1;
    dY = 0;
    animationHandle = PACMAN_LEFT_HANDLE;
  }
  
  else if(y < 490 && y<x && absX < 1 && M[pSquareY +1][pSquareX] != 'x')
  {
    dY = 1;
    dX = 0;
    animationHandle = PACMAN_DOWN_HANDLE;
  }
  else if(y > 530 && y>x && absX < 1 && M[pSquareY-1][pSquareX] != 'x')
  {
    dY = -1;
    dX = 0;
    animationHandle = PACMAN_UP_HANDLE;
  }
  
}

void DrawGrid()
{
  for(int i = 0; i < 34; i++)
  {
    GD.Vertex2ii(OFFSET_X,i*8);
    GD.Vertex2ii(480-OFFSET_X,i*8);
  }
  for(int i = 0; i < 60; i++)
  {
    GD.Vertex2ii(i*8,0);
    GD.Vertex2ii(i*8,480);
  }

  GD.Begin(RECTS);
  GD.Vertex2ii(pX,pY);
  GD.Vertex2ii(pX+8,pY+8);
}

void DrawPills()
{
  GD.Begin(POINTS);
  for(int i = 0; i < 28; i++)
  {
    for(int j = 0; j < 31; j++)
    {
      if(M[j][i] == '1' || M[j][i] == 'C')
      {
        GD.PointSize(20);
        int x = 131 + i*8;
        int y = 15 + j*8;
        GD.Vertex2ii(x,y);
      }
      else if(M[j][i] == 'S')
      {
        GD.PointSize(40);
        int x = 131 + i*8;
        int y = 15+j*8;
        GD.Vertex2ii(x,y);
      }
    }
  }
}

void EatPills()
{
  if(M[pSquareY][pSquareX] == '1')
  {
    GD.play(CHACK,40);
    M[pSquareY][pSquareX] = '0';
    highscore += 10;
    numPills--;
  }
  else if(M[pSquareY][pSquareX] == 'C')
  {
    GD.play(CHACK,40);
    M[pSquareY][pSquareX] = 'E';
    highscore += 10;
    numPills--;
  }
  else if(M[pSquareY][pSquareX] == 'S')
  {
    GD.play(HIHAT,40);
    M[pSquareY][pSquareX] = '0';
    highscore += 50;
    numPills--;
    blinky.scatter = true;
    clyde.scatter = true;
    inky.scatter = true;
    pinky.scatter = true;
    
    pinky.ChangeHandle();
    blinky.ChangeHandle();
    clyde.ChangeHandle();
    inky.ChangeHandle();
    pinky.ChangeHandle();
  }
}

void CountPills()
{
  for(int i = 0; i < 31; i++)
  {
    for(int j = 0; j < 28; j++)
    {
      if(M[i][j] == '1' || M[i][j] == 'C' || M[i][j] == 'S')
      {
        numPills++;
      }
    }
  }
}

void ResetPositions()
{
  if(lives > 0)
  {
    pX = STARTX;
    pY = STARTY;
    pSquareX = ((pX - OFFSET_X)*0.125)+0.5;
    pSquareY = (pY - OFFSET_Y)*0.125+0.5;
    animationHandle = PACMAN_LEFT_HANDLE;
    animationLimit = 3;
    anim = 0;
    
    blinky.ResetPosition(OFFSET_X+13*8, 11*8+OFFSET_Y);
    clyde.ResetPosition(OFFSET_X+15*8, 14*8+OFFSET_Y);
    inky.ResetPosition(OFFSET_X+11*8, 14*8+OFFSET_Y);
    pinky.ResetPosition(OFFSET_X+13*8, 14*8+OFFSET_Y);
    gameOver = false;
    delay(1000);
    lives--;
  }
}

void ResetGame()
{
  for(int i = 0; i < 31; i++)
  {
    for(int j = 0; j < 28; j++)
    {
      M[i][j] = originalMap[i][j];
    }
  }
  lives = 3;
  CountPills();
  ResetPositions();
}





