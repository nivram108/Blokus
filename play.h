#ifndef PLAY_H
#define PLAY_H

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
#include "ai.h"
using namespace std;

//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block : smallest unit on the board. 1x1 square.

class Play
{
private:
	Game game;
	AI ai;
	int instrCounter;
	int shapeID;
	char player;
	Shape selected;
    bool turn, isSelect;
    int endCounter;

public:
	Play();
	//Playing mode of 2 human players.
	void twoPlayers();
	//Playing mode of human v.s. Artificial Idiot
	void playerAI();
	//
	void priorityAdvantage();

	void init();
	void printBoard();
    string winner();
};


#endif
