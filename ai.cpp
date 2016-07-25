#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "shapes.h"
#include "ai.h"

#define RESET   ""
#define RED     ""      /* Red */
#define YELLOW  ""      /* Yellow */
#define MAGENTA ""      /* Magenta */

using namespace std;

// If autoPlay fails to place THE shape by random, place it by brutal force
void autoPlace(int id, char player)
{
    Shape selected;
    int counter  = 0;
    if (player == 'A')
        selected = shapesA[id];
    else
        selected = shapesB[id];

	for (int i=0; i<14; i++) {      //Brutal force placement
		for (int j=0; j<14; j++) {
			// two flip.
			for (int f=0; f<2; f++) {
				if (f > 0) selected.flip();
				// and four direction.
				for (int clockwise = 0; clockwise < 4; clockwise++) {
					if (clockwise > 0) selected.turnClockwise();
					if (isLegalMove(selected, i, j, player)) {
						// if this piece can put => return true.
						playerMove(selected, id, player, i, j);
						printBoard();
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
void autoPlay(char player)
{
    if (checkGameEndAI(player) == false)
        return;

    //init
    piecesPointer = (player == 'A') ? piecesA : piecesB;
    Shape selected;

    //select a shape
    int shapeID = rand()%21;
    // shape is unavailable or shape can't be placed
    while (piecesPointer[shapeID] == 0 || hasPlaceToPut(shapeID, player) == false)
        shapeID = rand()%21;
    selected = shapes[shapeID];
    //rand flip
    if (rand()%2 == 1)
        selected.flip();

    //rand turn
    int turn = rand()%4;
    for (int i=0; i<turn; i++)
        selected.turnClockwise();

    //rand place
    int x = rand()%14, y = rand()%14;
    while (playerMove(selected, shapeID, player, x, y) == false) { // move is illegal
        x = rand()%14;
        y = rand()%14;
    }
    piecesPointer[shapeID] = 0;
    cout << player << "'s step\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    return;
}

//mode of two Artificial Idiots battle.
void twoAIs()
{
    bool turn = 0;// A
    char player = (turn == 0) ? 'A' : 'B';
    piecesPointer = (player == 'A') ? piecesA : piecesB;
    string junk;
    while (checkGameEndAI('A') == true || checkGameEndAI('B') == true) {
        piecesPointer = (player == 'A') ? piecesA : piecesB;
        autoPlay(player);
        turn = !turn;
        cin >> junk;
        player = (turn == 0) ? 'A' : 'B';
    }
}
