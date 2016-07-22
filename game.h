#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "shapes.h"
#include "game.h"

#define RESET   ""
#define RED     ""      /* Red */
#define YELLOW  ""      /* Yellow */
#define MAGENTA ""      /* Magenta */

using namespace std;

int biggestRange = 0, bestA, bestB;
vector<shape> shapes, shapesA, shapesB;
char board[14][14];
char tmpBoard[14][14];
int shoulder[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int side[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

int first_step_flag_A = 0;
int first_step_flag_B = 0;
int *first_step_pointer;

int pieces_A[21] = {0};
int pieces_B[21] = {0};
int *pieces_pointer;

void listShapes(char player);

void printMap();

bool checkindex(int i);

bool isLegalFirst(shape shp, int x, int y, char player);

// connected to a shoulder
bool isConnectedToShoulder(shape shp, int x, int y, char player);

// touched by itself
bool isTouchedBySelf(shape shp, int x, int y, char player);

bool isSpare(shape shp, int x, int y, char player);

bool isLegalMove(shape shp, int x, int y, char player);

bool playerMove(shape shp, int shapeID, char player, int x, int y);

bool checkpieces(int id, char player);

bool checkgame(char player);

bool checkgameClear(char player);

void init();

string winner();

#endif
