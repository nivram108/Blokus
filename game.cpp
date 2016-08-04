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
//  block : smallest unit on the board. 1x1 square.

const int Game::shoulders[][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const int Game::sides[][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

Game::Game()
{
	this->biggestRange = 0;
	this->firstStepFlagA = false;
	this->firstStepFlagB = false;
	memset(this->piecesUseA, 0, sizeof(this->piecesUseA));
	memset(this->piecesUseB, 0, sizeof(this->piecesUseB));
}

//Initial the game.
//Create shapes and initial board and identifiers for placed shapes.
void Game::init()
{
	for (int i=0; i<14; i++)
		for (int j=0; j<14; j++)
			this->board[i][j] = '.';

	this->board[4][4] = 'A';
	this->board[9][9] = 'B';
	for (int i=0; i<21; i++) {
		this->piecesUseA[i] = false;
		this->piecesUseB[i] = false;
	}

	this->shapes.push_back(assignshape_00()); this->shapes.push_back(assignshape_01()); this->shapes.push_back(assignshape_02()); this->shapes.push_back(assignshape_03()); this->shapes.push_back(assignshape_04());
	this->shapes.push_back(assignshape_05()); this->shapes.push_back(assignshape_06()); this->shapes.push_back(assignshape_07()); this->shapes.push_back(assignshape_08()); this->shapes.push_back(assignshape_09());
	this->shapes.push_back(assignshape_10()); this->shapes.push_back(assignshape_11()); this->shapes.push_back(assignshape_12()); this->shapes.push_back(assignshape_13()); this->shapes.push_back(assignshape_14());
	this->shapes.push_back(assignshape_15()); this->shapes.push_back(assignshape_16()); this->shapes.push_back(assignshape_17()); this->shapes.push_back(assignshape_18()); this->shapes.push_back(assignshape_19());
	this->shapes.push_back(assignshape_20());
}

//Set all the pointers to the assigned player's
void Game::setPlayer(const char& player)
{
	this->piecesUsePointer = (player == 'A')? this->piecesUseA: this->piecesUseB;
}

//Get the shape of the assigned ID
Shape Game::getShape(const int& shapeID)
{
	if (shapeID<this->shapes.size() && shapeID>=0)
		return this->shapes[shapeID];

	Shape nullShape;
	return nullShape;
}

//Check if the selected piece used(true) or not(false)
bool Game::isPieceUse(const int& k)
{
	if (k>=0 && k<21)
		return this->piecesUsePointer[k];
	cout << "Game::isPieceUse: The argument is not between 0 and 21." << endl;
	return false;
}

//Set the selected piece used
void Game::setPieceUse(const int& k)
{
	if (k>=0 && k<21)
		this->piecesUsePointer[k] = true;
	else
		cout << "Game::setPieceUse: The argument is not between 0 and 21." << endl;
}

//Get bestA
int Game::getBestA()
{
	return this->bestA;
}

//Get bestB
int Game::getBestB()
{
	return this->bestB;
}

//List the shapes of the player that have not been placed yet.
void Game::listShapes(const char& player){
	//this->piecesUsePointer = (player == 'A'? this->piecesUseA : this->piecesUseB);
	if (player == 'A') {
		for (int i=0; i<21; i++) {
			if (!this->piecesUseA[i]) {
				cout << i << ":" << endl;
				this->shapes[i].printShape();
			}
		}
	}
	else {
		for (int i=0; i<21; i++) {
			if (!this->piecesUseB[i]) {
				cout << i << ":" << endl;
				this->shapes[i].printShape();
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
			if (this->board[i][j] == 'A')
				cout << YELLOW << 'A' << RESET;
			else if (this->board[i][j] == 'B')
				cout << RED << 'B' << RESET;
			else
				cout << this->board[i][j];
		}
		printf("\n");
	}
	cout << "|\n|---------------------------------\n" << endl;
}

//check if the selected shape index is between 0 and 20.
bool Game::checkShapeID(const int& i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

//Check if it's first step and if it's a legal first step.
bool Game::isLegalFirst(Shape& shp, const int& x, const int& y, const char& player)
{
	bool isLegal = false;
	if (player == 'A') {
		if (this->firstStepFlagA == false) {	// is first
			for (int i=0; i<shp.getSize(); i++) {
				if (x + shp.getPosX(i) == 4 && y + shp.getPosY(i) == 4)
					return true;
			}
		}
	}
	else {
		if (this->firstStepFlagB == false) {	// is first
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
bool Game::isConnectedToShoulder(Shape& shp, const int& x, const int& y, const char& player)
{
	for (int i=0; i<shp.getSize(); i++) {	//each block of the Shape
		for (int j=0; j<4; j++) { 	//each shoulder of the block
			if (this->board[shp.getPosX(i)+x+shoulders[j][0]][shp.getPosY(i)+y+shoulders[j][1]] == player && shp.getPosX(i)+x+shoulders[j][0]>=0 && shp.getPosX(i)+x+shoulders[j][0]<14&& shp.getPosY(i)+y+shoulders[j][1]>=0 && shp.getPosY(i)+y+shoulders[j][1]<14)
				return true;
		}
	}
	return false;
}

//touched by itself
//To check if the block is touched so it's ILLEGAL.
bool Game::isTouchedBySelf(Shape& shp, const int& x, const int& y, const char& player)
{
	for (int i=0; i<5; i++) {	//each block of the beside
		for (int j=0;j<4;j++) {	//each side of the block
			if (this->board[shp.getPosX(i)+x+sides[j][0]][shp.getPosY(i)+y+sides[j][1]] == player &&  shp.getPosX(i)+x+shoulders[j][0]>=0 && shp.getPosX(i)+x+shoulders[j][0]<14&& shp.getPosY(i)+y+shoulders[j][1]>=0 && shp.getPosY(i)+y+shoulders[j][1]<14)
				return true;
		}
	}
	return false;
}

//To check if the board is spare to place the block so it's LEGAL.
bool Game::isSpare(Shape& shp, const int& x, const int& y)
{
	for (int i=0; i<5; i++) {
		// The block is in board range and unoccupied.
		if ((shp.getPosX(i)+x < 14 && shp.getPosX(i)+x >= 0 && shp.getPosY(i)+y <14 && shp.getPosY(i)+y >= 0  && this->board[shp.getPosX(i)+x][shp.getPosY(i)+y] == '.')==false )
			return false;
	}
	return true;
}

//To check the move is legal or not, that is, Connected, not Touched and Spare to place.
bool Game::isLegalMove(Shape& shp, const int& x, const int& y, const char& player)
{
	bool firstStep = (player == 'A') ? this->firstStepFlagA : this->firstStepFlagB;
	if (firstStep == false) {	//is first step
		if (isLegalFirst(shp, x, y, player) == true)	// is first step
			return true;
		else
			return false;
	}

	if(!isConnectedToShoulder(shp, x, y, player)) {
		//cout << "The shape is not connected to any shoulder!" << endl;
		return false;
	}
	else if (isTouchedBySelf(shp, x, y, player)) {
		//cout << "The shape is touched by some sides!" << endl;
		return false;
	}
	else if (!isSpare(shp, x, y)) {
		//cout << "The position is illegal or used!" << endl;
		return false;
	}
	else
		return true;
}
//To tell why the move is illegal
string Game::reportIllegal(Shape& shp, const int& x, const int& y, const char& player)
{

	bool firstStep = (player == 'A') ? this->firstStepFlagA : this->firstStepFlagB;
	if (firstStep == false) {	//is first step
		if (isLegalFirst(shp, x, y, player) == true)	// is first step
			return "Is not a legal first step.";

	}

	if(!isConnectedToShoulder(shp, x, y, player)) {
		return "The shape is not connected to any shoulder!";
	}
	else if (isTouchedBySelf(shp, x, y, player)) {
		return "The shape is touched by some sides!";
	}
	else if (!isSpare(shp, x, y)) {
		return "The position is illegal or used!";
	}
}
//Make a single move. Return true if the move is success.
bool Game::playerMove(Shape& shp, const int& shapeID, const char& player, const int& x, const int& y)
{
	char junk, cX, cY;
	//this->piecesUsePointer = (player == 'A')? this->piecesUseA : this->piecesUseB;

	// shapeID is not between 0 and 21.
	if (shapeID>=21 || shapeID<0) {
		cout << "Game::playerMove: The argument is not between 0 and 21." << endl;
		return false;
	}

	// check if piece alredy been used.
	if (this->piecesUsePointer[shapeID])
		return false;

	// check if legal.
	if(isLegalMove(shp, x, y, player)) {
		for (int i=0; i<5; i++)
			this->board[shp.getPosX(i)+x][shp.getPosY(i)+y] = player;

		if (player == 'A')
			this->firstStepFlagA = true;
		else
			this->firstStepFlagB = true;

		printBoard();
		return true;
	}
	else
		return false;
}

//To check if the shape can be place anywhere or not.
bool Game::hasPlaceToPut(const int& id, const char& player)
{
	// loop though all board.
	Shape selected;
	int counter  = 0;
	if (id>=21 || id<0) {
		cout << "Game::hasPlaceToPut: The argument is not between 0 and 21." << endl;
		return false;
	}
	selected = this->shapes[id];

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
bool Game::isGameEnd(const char& player)
{
	cout << "\n\nstart check...\n" << endl;
	int counter = 0;
	bool cannot_put_any_pieces = true;
	this->piecesUsePointer = (player == 'A') ? this->piecesUseA : this->piecesUseB;
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i])
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i]) {
			if (hasPlaceToPut(i,player) == true)// can place
				cannot_put_any_pieces = false;// can place
		}
	}
	if (cannot_put_any_pieces == true) { // can't place, end.
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": You have no more pieces or you can't place any more.\n|" << endl;
		cout << counter << endl;
		return false;//end
	}
	else {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;//still
	}
}

//Checking game is ended or not, but without print anything. ( for AI )
bool Game::isGameEndAI(const char& player)
{
	int counter = 0;
	bool cannot_put_any_pieces = true;
	this->piecesUsePointer = (player == 'A') ? this->piecesUseA : this->piecesUseB;
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i])
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i]) {
			if (hasPlaceToPut(i, player) == true)
				cannot_put_any_pieces = false;
		}
	}
	
	if (cannot_put_any_pieces){
		cout << "press!!!" << player << endl;
		return false;
	}
	else{
		cout << "dont press!!!" << player << endl;
		return true;
	}
}

//To return the winner of the game.
string Game::winner()
{
	int ALeft = 0, BLeft = 0;
	for (int i=0; i<21; i++) {
		if (!this->piecesUseA[i])
			ALeft += this->shapes[i].getSize();
		if (!this->piecesUseB[i])
			BLeft += this->shapes[i].getSize();
	}

	if (ALeft - BLeft > this->biggestRange || BLeft - ALeft > this->biggestRange) {
		this->biggestRange = ALeft - BLeft;
		this->bestA = ALeft;
		this->bestB = BLeft;
	}
	cout << ALeft << " : " << BLeft << endl;
	return (ALeft < BLeft) ? "A" : "B";
}

