#pragma once
#include <GD2.h>
#include "Variables.h"

#define FRAMELIMIT 10

struct Ghost
{
    Ghost();
    Ghost(int x, int y, int ahandle, int id);
    void Update(int pacSquareX, int pacSquareY, Ghost ghost);
    bool CheckCollision();
    void Move(int pacSquareX, int pacSquareY, Ghost ghost);
    void Pathfinding(int pacSquareX, int pacSquareY, Ghost ghost , int multiplier);
    void ChangeHandle();
    void CheckGameOver(int pacSquareX, int pacSquareY);
    void ResetPosition(int x, int y);
    int handle;
    int secondHandle;
    int xPos;
    int yPos;
    int squareX;
    int squareY;

    int gDX = -1;
    int gDY = 0;

    int changeX = 0;
    int changeY = 0;
    
    int currentAnimation = 0;
    int animationFrame = 0;
    int animationLimit = 1;
    int frameCount = 0;
    int mode = 0;
    int ghostID;
    int absX = 0;
    int absY = 0;
    bool dead = false;
    bool scatter = false;
    int scatterFrame = 0;
    int pillLimit;
    bool exiting = true;
};

Ghost::Ghost()
{
  
}

Ghost::Ghost(int x, int y, int ahandle, int id)
{
  xPos = x;
  yPos = y;
  handle = ahandle;
  secondHandle = ahandle;
  ghostID = id;
  squareX = ((xPos - OFFSET_X)*0.125)+0.5;
  squareY = (yPos - OFFSET_Y)*0.125+0.5;
}

void Ghost::Update(int pacSquareX, int pacSquareY, Ghost ghost)
{
  GD.Begin(BITMAPS);
  
  frameCount++;
  squareX = ((xPos - OFFSET_X)*0.125)+0.5;
  squareY = ((yPos - OFFSET_Y)*0.125)+0.5;
  if(numPills <= pillLimit && exiting)
  {
    Move(13 ,11, *this);
    if(squareX == 13 && squareY == 11)
    {
      exiting = false;
    }
  }
  else if(!exiting)
  {
    Move(pacSquareX, pacSquareY,ghost);
  }
//  CheckGameOver(pacSquareX, pacSquareY);
  
  GD.Vertex2ii(xPos-7, yPos-7, handle, animationFrame);
  
  if(frameCount > FRAMELIMIT)
  {
    animationFrame++;
    frameCount = 0;
    if(animationFrame > animationLimit) animationFrame = currentAnimation;
  }
  if(scatter && !dead)
  {
    scatterFrame++;
    if(scatterFrame == 60*7)
    {
      animationLimit = 3;
    }
    else if(scatterFrame > 60*10)
    {
      scatter = false;
      ChangeHandle();
      scatterFrame = 0;
      
    }
  }
  if(squareX == 0 && squareY == 14 && gDX == -1)
  {
    squareX = 27;
    squareY = 14;
    xPos = (27*8)+OFFSET_X;
    yPos = (14*8)+OFFSET_Y;
  }
  else if(squareX == 27 && squareY == 14 && gDX == 1)
  {
    squareX = 0;
    squareY = 14;
    xPos = OFFSET_X;
    yPos = (14*8)+OFFSET_Y;
  }
//  GD.Begin(POINTS);
//  GD.PointSize(20);
//  GD.Vertex2ii(xPos, yPos);
//  GD.ColorRGB(0,255,0);
//  GD.Vertex2ii(OFFSET_X+(squareX*8), OFFSET_Y+(squareY*8));
//  delay(100);
}

void Ghost::Move(int pacSquareX, int pacSquareY,Ghost ghost)
{
  int tempX = (squareX*8 + OFFSET_X);
  int tempY = (squareY*8 + OFFSET_Y);
  
  absX = abs(tempX - xPos);
  absY = abs(tempY - yPos);
  
  if((M[squareY][squareX] == 'C' || M[squareY][squareX] == 'K' || M[squareY][squareX] == 'E' ||  M[squareY][squareX] == 'D') && absX < 1 && absY < 1)
  {
    if(!scatter)
    {
      int x = pacSquareX - squareX;
      int y = pacSquareY - squareY;
      int len = 8;
      switch(ghostID)
      {
        case 0: //Blinky
          Pathfinding(pacSquareX, pacSquareY,ghost,1);
          break;
        case 1: //Clyde
            if(len > 8) Pathfinding(pacSquareX,pacSquareY, ghost,1);
            else Pathfinding(2 ,30, ghost,1);      
          break;
        case 2: //Inky
          Pathfinding(pacSquareX, pacSquareY, ghost,2);
          break;
        case 3: //Pinky
          Pathfinding(pacSquareX, pacSquareY,ghost ,1);
          break;
      }
    }
    else if(dead)
    {
      Pathfinding(13, 14,*this,1);
      if(squareX == 13 && squareY == 14)
      {
        dead = false;
        scatter = false;
        exiting = true;
        ChangeHandle();
      }
    }
    else
    {
      switch(ghostID)
      {
        case 0: //Blinky
          Pathfinding(27, 1,ghost,1);
          break;
        case 1: //Clyde
          Pathfinding(2 ,30, ghost,1);      
          break;
        case 2: //Inky
          Pathfinding(26, 30, ghost,1);
          break;
        case 3: //Pinky
          Pathfinding(1, 1, ghost ,1);
          break;
      }
    }

  }
 
  if(M[squareY + gDY][squareX + gDX] == 'x' && absX < 1 && absY < 1)
  {
      if(M[squareY - 1][squareX] != 'x' && gDY != 1)
      {
        gDY = -1;
        gDX = 0;
        if(!scatter)
        {
          animationFrame = 6;
          animationLimit = 7;
          currentAnimation = 6;   
        }
        else if(dead)
        {
          animationFrame = 3;
          animationLimit = 3;
          currentAnimation = 3;   
        }
      }
      else if(M[squareY][squareX -1 ] != 'x' && gDX != 1)
      {
        gDY = 0;
        gDX = -1;
        if(!scatter)
        {
          animationFrame = 2;
          animationLimit = 3; 
          currentAnimation = 2;
        }
        else if(dead)
        {
          animationFrame = 1;
          animationLimit = 1;
          currentAnimation = 1;   
        }
      }
      else if(M[squareY + 1][squareX] != 'x'&& gDY != -1)
      {
        gDY = 1;
        gDX = 0;
        if(!scatter)
        {
          animationFrame = 0;
          animationLimit = 1;
          currentAnimation = 0;   
        }
        else if(dead)
        {
          animationFrame = 3;
          animationLimit = 3;
          currentAnimation = 3;   
        }
      }
      else if(M[squareY][squareX +1] != 'x'&& gDX != -1)
      {
        gDY = 0;
        gDX = 1;
        if(!scatter)
        {
          animationFrame = 4;
          animationLimit = 5;
          currentAnimation = 4;   
        }
        else if(dead)
        {
          animationFrame = 0;
          animationLimit = 0;
          currentAnimation = 0;   
        }
      }
  }
  else if(M[squareY + gDY][squareX + gDX] != 'x')
  {
    xPos += gDX;
    yPos += gDY;  
  }
  else if(absX >= 1 || absY >=1)
  {
    xPos += gDX;
    yPos += gDY;  
  }
}

void Ghost::Pathfinding(int pacSquareX, int pacSquareY, Ghost ghost ,int multiplier)
{
    bool restriction = M[squareY][squareX] == 'D' && !dead;
    int xDir1 = pacSquareX - ghost.squareX;
    int yDir1 = pacSquareY - (ghost.squareY-1);

    int xDir2 = pacSquareX - (ghost.squareX+1);
    int yDir2 = pacSquareY - ghost.squareY;

    int xDir3 = pacSquareX - (ghost.squareX-1);
    int yDir3 = pacSquareY - ghost.squareY;

    int xDir4 = pacSquareX - ghost.squareX;
    int yDir4 = pacSquareY - (ghost.squareY+1);

    int len1 = sqrt(xDir1*xDir1 + yDir1*yDir1)*multiplier;
    int len2 = sqrt(xDir2*xDir2 + yDir2*yDir2)*multiplier;
    int len3 = sqrt(xDir3*xDir3 + yDir3*yDir3)*multiplier;
    int len4 = sqrt(xDir4*xDir4 + yDir4*yDir4)*multiplier;

    int shortest1;
    int shortest2;
    
    shortest1 = min(len1, len2);
    shortest2 = min(len3, len4);
     
    int dir = min(shortest1, shortest2);
    int dir2 = max(shortest1, shortest2);
  
    if(dir == len1 && gDY != 1 && M[squareY-1][squareX] != 'x'){gDX = 0; gDY = -1; if(!scatter){ animationFrame = 6; animationLimit = 7; currentAnimation = 6; }}
    else if(dir == len2 && gDX != -1 && M[squareY][squareX+1] != 'x' ) {gDX = 1; gDY = 0; if(!scatter){ animationFrame = 4; animationLimit = 5; currentAnimation = 4;}}
    else if(dir == len3 && gDX != 1 && M[squareY][squareX-1] != 'x'){gDX = -1; gDY = 0; if(!scatter){ animationFrame = 2; animationLimit = 3; currentAnimation = 2;}}
    else if(dir == len4 && gDY != -1 && M[squareY+1][squareX] != 'x' && !restriction){gDX = 0; gDY = 1;if(!scatter){ animationFrame = 0; animationLimit = 1; currentAnimation = 0;}} 
    else
    {
      if(dir2 == len1 && gDY != 1 && M[squareY-1][squareX] != 'x'){gDX = 0; gDY = -1; if(!scatter){animationFrame = 6; animationLimit = 7; currentAnimation = 6;}}
      else if(dir2 == len2 && gDX != -1 && M[squareY][squareX+1] != 'x' ) {gDX = 1; gDY = 0;if(!scatter){ animationFrame = 4; animationLimit = 5; currentAnimation = 4;}}
      else if(dir2 == len3 && gDX != 1 && M[squareY][squareX-1] != 'x'){gDX = -1; gDY = 0;if(!scatter){ animationFrame = 2; animationLimit = 3; currentAnimation = 2;}}
      else if(dir2 == len4 && gDY != -1 && M[squareY+1][squareX] != 'x' && !restriction){gDX = 0; gDY = 1; if(!scatter){ animationFrame = 0; animationLimit = 1; currentAnimation = 0;}} 
    }
}

void Ghost::ChangeHandle()
{
  if(scatter && !dead)
  {
    handle = GHOST_HANDLE;
    animationFrame = 0;
    animationLimit = 1; 
    currentAnimation = 0;
    scatterFrame = 0;
  }
  else if(!scatter && !dead)
  {
    handle = secondHandle;
    animationFrame = 0;
    animationLimit = 1; 
    currentAnimation = 0;
  }
}

void Ghost::CheckGameOver(int pacSquareX, int pacSquareY)
{
  if(!scatter && pacSquareX == squareX && pacSquareY == squareY)
  {
    GD.play(TRUMPET);
    gameOver = true;
  }
  else if(scatter && (pacSquareX == squareX && pacSquareY == squareY) && !dead)
  {
    GD.play(SWITCH,40);
    handle = EYES_HANDLE;
    animationFrame = 0;
    animationLimit = 1; 
    currentAnimation = 0;
    dead = true;
    highscore += 100;
  }
}

void Ghost::ResetPosition(int x, int y)
{
  xPos = x;
  yPos = y;
  squareX = ((xPos - OFFSET_X)*0.125)+0.5;
  squareY = (yPos - OFFSET_Y)*0.125+0.5;
  exiting = true;
}


