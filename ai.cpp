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

void autoPlace(int id, char player)
{
    shape selected;
    int counter  = 0;
    if (player == 'A')
        selected = shapesA[id];
    else
        selected = shapesB[id];

	for (int i=0; i<14; i++) {
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
						printMap();
						return ;
					}
				}
			}
		}
	}
	return;
}

void autoPlay(char player)
{
    if (checkgameClear(player) == false)
        return;

    //init
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
    vector <shape> autoShape = (player == 'A') ? shapesA : shapesB;
    shape selected;

    //select a shape
    int shapeID = rand()%21;
    // shape is unavailable or shape can't be placed
    while (pieces_pointer[shapeID] == 0 || checkpieces(shapeID, player) == false)
        shapeID = rand()%21;
    selected = autoShape[shapeID];

    //rand flip
    if (rand()%2 == 1)
        selected.flip();

    //rand turn
    int turn = rand()%4;
    for (int i=0; i<turn; i++)
        selected.turnClockwise();

    //rand place
    int x = rand()%14, y = rand()%14;
    int struggle = 196;
    while (playerMove(selected, shapeID, player, x, y) == false) { // move is illegal
        struggle--;
        if (struggle == 0)
        {
            autoPlace(shapeID, player);
            break;
        }
        x = rand()%14;
        y = rand()%14;
    }
    pieces_pointer[shapeID] = 0;
    cout << player << "'s step\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    return;
}

void autoGame()
{
    bool turn = 0;// A
    char player = (turn == 0) ? 'A' : 'B';
    first_step_pointer = (player == 'A')? &first_step_flag_A: &first_step_flag_B;
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
    string junk;
    while (checkgameClear('A') == true || checkgameClear('B') == true) {
        pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
        autoPlay(player);
        turn = !turn;
        cin >> junk;
        player = (turn == 0) ? 'A' : 'B';
    }
}
