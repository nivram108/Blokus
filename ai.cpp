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

// If autoPlay fails to place THE shape by random, place it by brutal force
void AI::autoPlace(int id, char player)
{
    Shape selected;
    int counter  = 0;
    selected = game.getShape(id);

	for (int i=0; i<14; i++) {      //Brutal force placement
		for (int j=0; j<14; j++) {
			// two flip.
			for (int f=0; f<2; f++) {
				if (f > 0) selected.flip();
				// and four direction.
				for (int clockwise = 0; clockwise < 4; clockwise++) {
					if (clockwise > 0) selected.turnClockwise();
					if (game.isLegalMove(selected, i, j, player)) {
						// if this piece can put => return true.
						game.playerMove(selected, id, player, i, j);
						game.printBoard();
						return ;
					}
				}
			}
		}
	}
	return;
}

//Play a round for Artificial Idiot. Random everything.
//Random pick a unplaced shape, random flip and turn, random place*
//If random place fails too many time, call autoPlace.
void AI::autoPlay(char player)
{
    if (game.isGameEndAI(player) == false)
        return;

    //init
    game.setPlayer(player);
    Shape selected;

    //select a shape
    int shapeID = rand()%21;
    // shape is unavailable or shape can't be placed
    while (game.isPieceUse(shapeID) || game.hasPlaceToPut(shapeID, player) == false)
        shapeID = rand()%21;
    selected = game.getShape(shapeID);
    //rand flip
    if (rand()%2 == 1)
        selected.flip();

    //rand turn
    int turn = rand()%4;
    for (int i=0; i<turn; i++)
        selected.turnClockwise();

    //rand place
    int x = rand()%14, y = rand()%14;
    while (game.playerMove(selected, shapeID, player, x, y) == false) { // move is illegal
        x = rand()%14;
        y = rand()%14;
    }
    game.setPieceUse(shapeID);
    cout << player << "'s step\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    return;
}

//mode of two Artificial Idiots battle.
void AI::twoAIs()
{
    bool turn = 0;// A
    char player = (turn == 0) ? 'A' : 'B';
    string junk;
    while (game.isGameEndAI('A') == true || game.isGameEndAI('B') == true) {
        game.setPlayer(player);
        autoPlay(player);
        turn = !turn;
        cin >> junk;
        player = (turn == 0) ? 'A' : 'B';
    }
}
