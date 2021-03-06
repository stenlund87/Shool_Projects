#pragma once

#define TILESIZE 8
#define ANIMATIONTIME 10

#define STARTX 244
#define STARTY 199

#define OFFSET_X 132
#define OFFSET_Y 15

#define BLINKYID 0
#define CLYDEID 1
#define INKYID 2
#define PINKYID 3

#define SW_PIN 46
#define X_PIN 14
#define Y_PIN 15
bool gameOver = false;
int highscore = 0;
int numPills = 0;

//Map representation as a char array
//x are walls
//1 are walkable area with pill
//0 are walkable area without pill
//C are walkable area with pill and it is an intersection
//K are walkable area with pill and it is an intersection
char M[][28] = {
{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
{'x','1','1','1','1','1','C','1','1','1','1','1','1','x','x','1','1','1','1','1','1','C','1','1','1','1','1','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','S','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','S','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','C','1','1','1','1','C','1','1','C','1','1','C','1','1','C','1','1','C','1','1','C','1','1','1','1','C','x'},
{'x','1','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','1','x'},
{'x','1','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','1','x'},
{'x','1','1','1','1','1','C','x','x','1','1','1','1','x','x','1','1','1','1','x','x','C','1','1','1','1','1','x'},
{'x','x','x','x','x','x','1','x','x','x','x','x','0','x','x','0','x','x','x','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','x','x','x','0','x','x','0','x','x','x','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','0','0','K','D','D','K','0','0','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','D','D','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','E','E','E','E','E','E','x','0','x','x','1','x','x','x','x','x','x'},
{'0','0','0','0','0','0','C','0','0','K','x','E','E','E','E','E','E','x','K','0','0','C','0','0','0','0','0','0'},
{'x','x','x','x','x','x','1','x','x','0','x','E','E','E','E','E','E','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','x','x','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','K','0','0','0','0','0','0','0','0','K','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','x','x','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','x','x','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','1','1','1','1','1','C','1','1','C','1','1','1','x','x','1','1','1','C','1','1','C','1','1','1','1','1','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','S','1','1','x','x','C','1','1','C','1','1','C','0','0','C','1','1','C','1','1','C','x','x','1','1','S','x'},
{'x','x','x','1','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','1','x','x','x'},
{'x','x','x','1','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','1','x','x','x'},
{'x','1','1','C','1','1','1','x','x','1','1','1','1','x','x','1','1','1','1','x','x','1','1','1','C','1','1','x'},
{'x','1','x','x','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','x','x','1','x'},
{'x','1','x','x','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','x','x','1','x'},
{'x','1','1','1','1','1','1','1','1','1','1','1','C','1','1','C','1','1','1','1','1','1','1','1','1','1','1','x'},
{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'}
};


char originalMap[][28] = {
{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
{'x','1','1','1','1','1','C','1','1','1','1','1','1','x','x','1','1','1','1','1','1','C','1','1','1','1','1','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','S','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','S','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','C','1','1','1','1','C','1','1','C','1','1','C','1','1','C','1','1','C','1','1','C','1','1','1','1','C','x'},
{'x','1','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','1','x'},
{'x','1','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','1','x'},
{'x','1','1','1','1','1','C','x','x','1','1','1','1','x','x','1','1','1','1','x','x','C','1','1','1','1','1','x'},
{'x','x','x','x','x','x','1','x','x','x','x','x','0','x','x','0','x','x','x','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','x','x','x','0','x','x','0','x','x','x','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','0','0','K','0','0','K','0','0','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','E','E','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','E','E','E','E','E','E','x','0','x','x','1','x','x','x','x','x','x'},
{'0','0','0','0','0','0','C','0','0','K','x','E','E','E','E','E','E','x','K','0','0','C','0','0','0','0','0','0'},
{'x','x','x','x','x','x','1','x','x','0','x','E','E','E','E','E','E','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','x','x','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','K','0','0','0','0','0','0','0','0','K','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','x','x','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','x','x','x','x','x','1','x','x','0','x','x','x','x','x','x','x','x','0','x','x','1','x','x','x','x','x','x'},
{'x','1','1','1','1','1','C','1','1','C','1','1','1','x','x','1','1','1','C','1','1','C','1','1','1','1','1','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','1','x','x','x','x','1','x','x','x','x','x','1','x','x','1','x','x','x','x','x','1','x','x','x','x','1','x'},
{'x','S','1','1','x','x','C','1','1','C','1','1','C','0','0','C','1','1','C','1','1','C','x','x','1','1','S','x'},
{'x','x','x','1','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','1','x','x','x'},
{'x','x','x','1','x','x','1','x','x','1','x','x','x','x','x','x','x','x','1','x','x','1','x','x','1','x','x','x'},
{'x','1','1','C','1','1','1','x','x','1','1','1','1','x','x','1','1','1','1','x','x','1','1','1','C','1','1','x'},
{'x','1','x','x','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','x','x','1','x'},
{'x','1','x','x','x','x','x','x','x','x','x','x','1','x','x','1','x','x','x','x','x','x','x','x','x','x','1','x'},
{'x','1','1','1','1','1','1','1','1','1','1','1','C','1','1','C','1','1','1','1','1','1','1','1','1','1','1','x'},
{'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'}
};

