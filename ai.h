#ifndef AI_H
#define AI_H

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
using namespace std;

//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block : smallest unit on the board. 1x1 square.

class AI
{
private:
	Game game;
public:
	//AI();

	// If autoPlay fails to place THE shape by random, place it by brutal force
	void autoPlace(int id, char player);
	//Play a round for Artificial Idiot. Random everything.
	void autoPlay(char player);
	//mode of two Artificial Idiots battle.
	void twoAIs();
};

#endif
