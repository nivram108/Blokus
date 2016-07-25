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
