#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <cstring>
#include "shapes.h"
#include "game.h"
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */

//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block :

const int Game::shoulders[][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const int Game::sides[][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

Game::Game()
{
    biggestRange = 0;
    firstStepFlagA = 0;
    firstStepFlagB = 0;
    memset(piecesA, 0, sizeof(piecesA));
    memset(piecesB, 0, sizeof(piecesB));
}

//Initial the game.
//Create shapes and initial board and identifiers for placed shapes.
void Game::init()
{
    for (int i=0; i<14; i++)
        for (int j=0; j<14; j++)
            board[i][j] = '.';

    board[4][4] = 'A';
    board[9][9] = 'B';
    for (int i=0; i<21; i++) {
        piecesA[i] = 1;
        piecesB[i] = 1;
    }

    shapes.push_back(assignshape_00());shapes.push_back(assignshape_01());shapes.push_back(assignshape_02());shapes.push_back(assignshape_03());shapes.push_back(assignshape_04());
    shapes.push_back(assignshape_05());shapes.push_back(assignshape_06());shapes.push_back(assignshape_07());shapes.push_back(assignshape_08());shapes.push_back(assignshape_09());
    shapes.push_back(assignshape_10());shapes.push_back(assignshape_11());shapes.push_back(assignshape_12());shapes.push_back(assignshape_13());shapes.push_back(assignshape_14());
    shapes.push_back(assignshape_15());shapes.push_back(assignshape_16());shapes.push_back(assignshape_17());shapes.push_back(assignshape_18());shapes.push_back(assignshape_19());
    shapes.push_back(assignshape_20());
    shapesA = shapesB = shapes;
}

//List the shapes of the player that have not been placed yet.
void Game::listShapes(char player){
	piecesPointer = (player == 'A'? piecesA : piecesB);
    if (player == 'A') {
        for (int i=0; i<21; i++) {
        	if (piecesPointer[i] == 1) {
				cout << i << ":" << endl;
            	shapesA[i].printShape();
        	}
        }
    }
    else {
        for (int i=0; i<21; i++) {
        	if (piecesPointer[i] == 1) {
				cout << i << ":" << endl;
            	shapesB[i].printShape();
        	}
        }
    }
}

//Print out the current board status.
void Game::printBoard()
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

//check if the selected shape index is between 0 and 20.
bool Game::checkShapeID(int i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

//Check if it's first step and if it's a legal first step.
bool Game::isLegalFirst(Shape shp, int x, int y, char player)
{
    bool isLegal = false;
    if (player == 'A') {
        if (firstStepFlagA == 0) {	// is first
            for (int i=0; i<shp.getSize(); i++) {
                if (x + shp.getPosX(i) == 4 && y + shp.getPosY(i) == 4)
                    return true;
            }
        }
    }
    else {
        if (firstStepFlagB == 0) {	// is first
            for (int i=0;i<shp.getSize();i++) {
                if (x + shp.getPosX(i) == 9 && y + shp.getPosY(i) == 9)
                	return true;
            }
        }
    }
    return false;
}

//connected to a shoulder
//To check if the block is connected so it's LEGAL.
bool Game::isConnectedToShoulder(Shape shp, int x, int y, char player)
{
	for (int i=0; i<shp.getSize(); i++) {	//each block of the Shape
	    for (int j=0; j<4; j++) { 	//each shoulder of the block
	        if (board[shp.getPosX(i)+x+shoulders[j][0]][shp.getPosY(i)+y+shoulders[j][1]] == player && shp.getPosX(i)+x+shoulders[j][0]>=0 && shp.getPosX(i)+x+shoulders[j][0]<14&& shp.getPosY(i)+y+shoulders[j][1]>=0 && shp.getPosY(i)+y+shoulders[j][1]<14)
	            return true;
	    }
	}
    return false;
}

//touched by itself
//To check if the block is touched so it's ILLEGAL.
bool Game::isTouchedBySelf(Shape shp, int x, int y, char player)
{
	for (int i=0; i<5; i++) {	//each block of the beside
	    for (int j=0;j<4;j++) {	//each side of the block
	        if (board[shp.getPosX(i)+x+sides[j][0]][shp.getPosY(i)+y+sides[j][1]] == player &&  shp.getPosX(i)+x+shoulders[j][0]>=0 && shp.getPosX(i)+x+shoulders[j][0]<14&& shp.getPosY(i)+y+shoulders[j][1]>=0 && shp.getPosY(i)+y+shoulders[j][1]<14)
	          	return true;
        }
    }
    return false;
}

//To check if the board is spare to place the block so it's LEGAL.
bool Game::isSpare(Shape shp, int x, int y, char player)
{
    for (int i=0; i<5; i++) {
	    if ((shp.getPosX(i)+x < 14 && shp.getPosX(i)+x >= 0 && shp.getPosY(i)+y <14 && shp.getPosY(i)+y >= 0  && board[shp.getPosX(i)+x][shp.getPosY(i)+y] == '.')==false ) // the block is in board range and unoccupied
	        return false;
    }
    return true;
}

//To check the move is legal or not, that is, Connected, not Touched and Spare to place.
bool Game::isLegalMove(Shape shp, int x, int y, char player)
{
    int firstStep = (player == 'A') ? firstStepFlagA : firstStepFlagB;
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

//Make a single move. Return true if the move is success.
bool Game::playerMove(Shape shp, int shapeID, char player, int x, int y)
{
    char junk, cX, cY;
    firstStepPointer = (player == 'A')? &firstStepFlagA : &firstStepFlagB;
    piecesPointer = (player == 'A')? piecesA : piecesB;
    // check if piece alredy been used.
    if (piecesPointer[shapeID] == 0)
     	return false;

    // check if legal.
	if(isLegalMove(shp, x, y, player)) {
		for (int i=0; i<5; i++)
		    board[shp.getPosX(i)+x][shp.getPosY(i)+y] = player;

		if (player == 'A')
            firstStepFlagA = 1;
        else
            firstStepFlagB = 1;

		printBoard();
		return true;
	}
	else
		return false;
}

//To check if the shape can be place anywhere or not.
bool Game::hasPlaceToPut(int id, char player)
{
	// loop though all board.
	Shape selected;
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
	return false; // if this piece can't   => return false.
}

//To check if the game is ended.
bool Game::isGameEnd(char player)
{
	cout << "\n\nstart check...\n" << endl;
	int counter = 0;
	bool cannot_put_any_pieces = true;
    piecesPointer = (player == 'A') ? piecesA : piecesB;
	for (int i=0; i<21; i++) {
		if (piecesPointer[i] == 1)
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (piecesPointer[i] == 1) {
 			if (hasPlaceToPut(i,player) == true)// can place
                cannot_put_any_pieces = false;// can place
		}
	}
	if (cannot_put_any_pieces == true) { // can't place, end.
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << "You have no more pieces or you can't place any more.\n|" << endl;
		cout<<counter<<endl;
		return false;//end
	}
	else {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;//still
	}
}

//Checking game is ended or not, but without print anything. ( for AI )
bool Game::checkGameEndAI(char player)
{
	int counter = 0;
	bool cannot_put_any_pieces = true;
    piecesPointer = (player == 'A') ? piecesA : piecesB;
	for (int i=0; i<21; i++) {
		if (piecesPointer[i] == 1)
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (piecesPointer[i] == 1) {
			if (hasPlaceToPut(i,player) == true)
                cannot_put_any_pieces = false;
		}
	}
	if (cannot_put_any_pieces)
		return false;
	else
		return true;
}

//To return the winner of the game.
string Game::winner()
{
    int ALeft = 0, BLeft = 0;
    for (int i=0; i<21; i++) {
        if (piecesA[i] == 1)
            ALeft += shapesA[i].getSize();
        if (piecesB[i] == 1)
            BLeft += shapesB[i].getSize();
    }

    if (ALeft - BLeft > biggestRange || BLeft - ALeft > biggestRange) {
        biggestRange = ALeft - BLeft;
        bestA = ALeft;
        bestB = BLeft;
    }
    cout << ALeft << " : " << BLeft << endl;
    return (ALeft < BLeft) ? "A" : "B";
}
