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

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */
//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block : smallest unit on the board. 1x1 square.
using namespace std;

class Play
{
private:
	Game game;
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
