// This file was generated with the command-line:
//    /usr/local/bin/gd2asset -f myasset.gd2 -o myasset.h pm.jpg pacman_up.png pacman_left.png pacman_down.png pacman_right.png Blinky.png Clyde.png Eyes.png Ghost.png Inky.png pacman_death15x13.png Pinky.png

#define PM_HANDLE 0
#define PM_WIDTH 256
#define PM_HEIGHT 256
#define PM_CELLS 1
#define PACMAN_UP_HANDLE 1
#define PACMAN_UP_WIDTH 13
#define PACMAN_UP_HEIGHT 39
#define PACMAN_UP_CELLS 1
#define PACMAN_LEFT_HANDLE 2
#define PACMAN_LEFT_WIDTH 13
#define PACMAN_LEFT_HEIGHT 39
#define PACMAN_LEFT_CELLS 1
#define PACMAN_DOWN_HANDLE 3
#define PACMAN_DOWN_WIDTH 13
#define PACMAN_DOWN_HEIGHT 39
#define PACMAN_DOWN_CELLS 1
#define PACMAN_RIGHT_HANDLE 4
#define PACMAN_RIGHT_WIDTH 13
#define PACMAN_RIGHT_HEIGHT 39
#define PACMAN_RIGHT_CELLS 1
#define BLINKY_HANDLE 5
#define BLINKY_WIDTH 14
#define BLINKY_HEIGHT 112
#define BLINKY_CELLS 1
#define CLYDE_HANDLE 6
#define CLYDE_WIDTH 14
#define CLYDE_HEIGHT 112
#define CLYDE_CELLS 1
#define EYES_HANDLE 7
#define EYES_WIDTH 14
#define EYES_HEIGHT 56
#define EYES_CELLS 1
#define GHOST_HANDLE 8
#define GHOST_WIDTH 14
#define GHOST_HEIGHT 56
#define GHOST_CELLS 1
#define INKY_HANDLE 9
#define INKY_WIDTH 14
#define INKY_HEIGHT 112
#define INKY_CELLS 1
#define PACMAN_DEATH15X13_HANDLE 10
#define PACMAN_DEATH15X13_WIDTH 15
#define PACMAN_DEATH15X13_HEIGHT 156
#define PACMAN_DEATH15X13_CELLS 1
#define PINKY_HANDLE 11
#define PINKY_WIDTH 14
#define PINKY_HEIGHT 112
#define PINKY_CELLS 1
#define ASSETS_END 155488UL
#define LOAD_ASSETS()  (GD.safeload("myasset.gd2"))

static const shape_t PM_SHAPE = {0, 256, 256, 0};
static const shape_t PACMAN_UP_SHAPE = {1, 13, 39, 0};
static const shape_t PACMAN_LEFT_SHAPE = {2, 13, 39, 0};
static const shape_t PACMAN_DOWN_SHAPE = {3, 13, 39, 0};
static const shape_t PACMAN_RIGHT_SHAPE = {4, 13, 39, 0};
static const shape_t BLINKY_SHAPE = {5, 14, 112, 0};
static const shape_t CLYDE_SHAPE = {6, 14, 112, 0};
static const shape_t EYES_SHAPE = {7, 14, 56, 0};
static const shape_t GHOST_SHAPE = {8, 14, 56, 0};
static const shape_t INKY_SHAPE = {9, 14, 112, 0};
static const shape_t PACMAN_DEATH15X13_SHAPE = {10, 15, 156, 0};
static const shape_t PINKY_SHAPE = {11, 14, 112, 0};

