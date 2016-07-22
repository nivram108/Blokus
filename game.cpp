#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "shapes.h"

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

void listShapes(char player){
	pieces_pointer = (player == 'A'? pieces_A : pieces_B);
    if (player == 'A') {
        for (int i=0; i<21; i++) {
        	if (pieces_pointer[i] == 1) {
				cout << i << ":" << endl;
            	shapesA[i].printShape();
        	}
        }
    }
    else {
        for (int i=0; i<21; i++) {
        	if (pieces_pointer[i] == 1) {
				cout << i << ":" << endl;
            	shapesB[i].printShape();
        	}
        }
    }
}

void printMap()
{
	cout << "|---------------------------------\n| [Map]" << endl;
    cout << "|\t            1111" << endl;
    cout << "|\t  ";
    for (int i=0; i<14; i++) {
    	if (i == 4 || i == 9)
    		cout << MAGENTA << i%10 << RESET;
    	else
    		cout << i%10;
    }

    cout << endl;

    for (int i=0; i<14; i++) {
        if (i>=10)
            cout << "|\t" << 1;
        else
            cout << "|\t ";

    	if (i == 4 || i == 9)
    		cout << MAGENTA << i%10 << RESET;
    	else
    		cout << i%10;

        for (int j=0; j<14; j++) {
        	if (board[i][j] == 'A')
        		cout << YELLOW << 'A' << RESET;
        	else if (board[i][j] == 'B')
        		cout << RED << 'B' << RESET;
        	else
        		cout << board[i][j];
        }
        printf("\n");
    }
    cout << "|\n|---------------------------------\n" << endl;
}

bool checkindex(int i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

bool isLegalFirst(shape shp, int x, int y, char player)
{
    bool isLegal = false;
    if (player == 'A') {
        if (first_step_flag_A == 0) {	// is first
            for (int i=0; i<shp.size; i++) {
                if (x + shp.x[i] == 4 && y + shp.y[i] == 4)
                    return true;
            }
        }
    }
    else {
        if (first_step_flag_B == 0) {	// is first
            for (int i=0;i<shp.size;i++) {
                if (x + shp.x[i] == 9 && y + shp.y[i] == 9)
                	return true;
            }
        }
    }
    return false;
}

// connected to a shoulder
bool isConnectedToShoulder(shape shp, int x, int y, char player)
{
	for (int i=0; i<shp.size; i++) {	//each block of the shape
	    for (int j=0; j<4; j++) { 	//each shoulder of the block
	        if (board[shp.x[i]+x+shoulder[j][0]][shp.y[i]+y+shoulder[j][1]] == player && checkindex(shp.x[i]+x+shoulder[j][0])&& checkindex(shp.y[i]+y+shoulder[j][1]))
	            return true;
	    }
	}
    return false;
}

// touched by itself
bool isTouchedBySelf(shape shp, int x, int y, char player)
{
	for (int i=0; i<5; i++) {	//each block of the beside
	    for (int j=0;j<4;j++) {	//each side of the block
	        if (board[shp.x[i]+x+side[j][0]][shp.y[i]+y+side[j][1]] == player && checkindex(shp.x[i]+x+side[j][0]) && checkindex(shp.y[i]+y+side[j][1]))
	          	return true;
        }
    }
    return false;
}

bool isSpare(shape shp, int x, int y, char player)
{
    for (int i=0; i<5; i++) {
	    if ((shp.x[i]+x < 14 && shp.x[i]+x >= 0 && shp.y[i]+y <14 && shp.y[i]+y >= 0  && board[shp.x[i]+x][shp.y[i]+y] == '.')==false ) // the block is in board range and unoccupied
	        return false;
    }
    return true;
}

bool isLegalMove(shape shp, int x, int y, char player)
{
    int firstStep = (player == 'A') ? first_step_flag_A : first_step_flag_B;
    if (firstStep == 0) {	//is first step
        if (isLegalFirst(shp, x, y, player) == true)	// is first step
            return true;
        else
            return false;
    }

    if( isConnectedToShoulder(shp, x, y, player)==false || isTouchedBySelf(shp, x, y, player)==true || isSpare(shp, x, y, player) ==false )
        return false;
    else
        return true;

    return false;
}

bool playerMove(shape shp, int shapeID, char player, int x, int y)
{
    char junk, cX, cY;
    first_step_pointer = (player == 'A')? &first_step_flag_A : &first_step_flag_B;
    pieces_pointer = (player == 'A')? pieces_A : pieces_B;
    // check if piece alredy been used.
    if (pieces_pointer[shapeID] == 0)
     	return false;

    // check if legal.
	if(isLegalMove(shp, x, y, player)) {
		for (int i=0; i<5; i++)
		    board[shp.x[i]+x][shp.y[i]+y] = player;

		if (player == 'A')
            first_step_flag_A = 1;
        else
            first_step_flag_B = 1;

		printMap();
		return true;
	}
	else
		return false;
}

bool checkpieces(int id, char player)
{
	// loop though all board.
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

					// if this piece can put => return true.
					if(isLegalMove(selected, i, j, player))
						return true;
				}
			}
		}
	}
	return false; // if this piece can`t   => return false.
}

bool checkgame(char player)
{
	cout << "\n\nstart check...\n" << endl;
	int counter = 0;
	bool cannot_put_any_pieces = true;
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
	for (int i=0; i<21; i++) {
		if (pieces_pointer[i] == 1)
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (pieces_pointer[i] == 1) {
 			if (checkpieces(i,player) == true)// can place
                cannot_put_any_pieces = false;// can place
		}
	}
	if (cannot_put_any_pieces == true) { // can't place, end.
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << "You have no more pieces or you can`t place any more.\n|" << endl;
		cout<<counter<<endl;
		return false;//end
	}
	else {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;//still
	}
}

bool checkgameClear(char player)
{
	int counter = 0;
	bool cannot_put_any_pieces = true;
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
	for (int i=0; i<21; i++) {
		if (pieces_pointer[i] == 1)
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (pieces_pointer[i] == 1) {
			if (checkpieces(i,player) == true)
                cannot_put_any_pieces = false;
		}
	}
	if (cannot_put_any_pieces)
		return false;
	else
		return true;
}

void init()
{
    for (int i=0; i<14; i++)
        for (int j=0; j<14; j++)
            board[i][j] = '.';

    board[4][4] = 'A';
    board[9][9] = 'B';
    for (int i=0; i<21; i++) {
    	pieces_A[i] = 1;
    	pieces_B[i] = 1;
    }

    shapes.push_back(assignshape_00());shapes.push_back(assignshape_01());shapes.push_back(assignshape_02());shapes.push_back(assignshape_03());shapes.push_back(assignshape_04());
    shapes.push_back(assignshape_05());shapes.push_back(assignshape_06());shapes.push_back(assignshape_07());shapes.push_back(assignshape_08());shapes.push_back(assignshape_09());
    shapes.push_back(assignshape_10());shapes.push_back(assignshape_11());shapes.push_back(assignshape_12());shapes.push_back(assignshape_13());shapes.push_back(assignshape_14());
    shapes.push_back(assignshape_15());shapes.push_back(assignshape_16());shapes.push_back(assignshape_17());shapes.push_back(assignshape_18());shapes.push_back(assignshape_19());
    shapes.push_back(assignshape_20());
    shapesA = shapesB = shapes;
}

string winner()
{
    int ALeft = 0, BLeft = 0;
    for (int i=0; i<21; i++) {
        if (pieces_A[i] == 1)
            ALeft += shapesA[i].size;
        if (pieces_B[i] == 1)
            BLeft += shapesB[i].size;
    }

    if (ALeft - BLeft > biggestRange || BLeft - ALeft > biggestRange) {
        biggestRange = ALeft - BLeft;
        bestA = ALeft;
        bestB = BLeft;
    }
    cout << ALeft << " : " << BLeft << endl;
    return (ALeft < BLeft) ? "A" : "B";
}
