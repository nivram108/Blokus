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
#include "play.h"
using namespace std;

//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block : smallest unit on the board. 1x1 square.

Play::Play()
{
	this->game.init();
	this->game.setPlayer('A');

	this->instrCounter = 1;

	this->selectShape = false;
	this->selected = this->game.getShape(0);
}

//The assigned player plays the game. True when the game is quitted.
bool Play::playerPlay(const char& player)
{
	int instr;
	this->selectShape = false;

	while (true) {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| [instruction #" << this->instrCounter << "] you can press 1~7:" << "\n|\n";
		cout << "|\t1) Select a shape\n|\t2) Flip\n|\t3) Rotate clockwise\n|\t4) Next move\n|\t5) Print the board\n|\t6) List remaining shapes\n|\t7) Check the condition\n|\t999) EXIT\n|\n";
		cout << "|--------------------------------- " << endl;
		cout << " Blockus>>";

		cin >> instr;
		if (instr == 999)
			return true;
		if (instr == 1) {		// Select a shape
			cout<<"shape index:";
			int tmpID;
			cin >> tmpID;

			if (this->game.checkShapeID(tmpID)) {
				if (this->game.isPieceUse(tmpID)) {
					cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
					continue;
				}
				else {
					this->selectShape = true;
					this->shapeID = tmpID;
					this->selected = this->game.getShape(this->shapeID);
					this->selected.printShape();
				}
			}
			else {
				cout << "We don't have this index! Please retry the instruction!" << endl;
				continue;
			}
		}
		else if (instr == 2) {	// Flip
			if (this->selectShape == false) {
				cout << "Please Select a shape." << endl;
				continue;
			}
			this->selected.flip();
			this->selected.printShape();
		}
		else if (instr == 3) { // Rotate clockwise
			if (this->selectShape == false) {
				cout << "Please Select a shape." << endl;
				continue;
			}
			this->selected.turnClockwise();
			this->selected.printShape();
		}
		else if (instr == 4) { // Next move
			cout << "shapeID:" << this->shapeID << endl;
			this->game.printBoard();
			if (this->selectShape == false) {	//Hasn't select yet
				cout << "Please Select a shape." << endl;
				continue;
			}
			this->selected.printShape();
			
			int x, y;
			cout << "[ " << player << "'s turn ] input x, y:";
			cin >> x >> y;
			if ( this->game.playerMove(this->selected, this->shapeID, player, x, y) ) {
				this->game.setPieceUse(this->shapeID);
				this->instrCounter++;
				return false;
			}
			else
				cout << this->game.getErrMsg() << endl;
		}
		else if (instr == 5) {	// Print the board
			this->game.printBoard();
		}
		else if (instr == 6) {	// List remaining shapes
			this->game.listShapes(player);
		}
		else if (instr == 7) {	// Check the condition
			this->game.isGameAlive(player);
		}
		else {
			cout<<"Not a command."<<endl;
		}
	}
}

// If autoPlay fails to place THE shape by random, place it by brutal force.
void Play::autoPlace(const int& id, const char& player)
{
	Shape selected;
	int counter  = 0;
	selected = game.getShape(id);

	for (int i=0; i<14; i++) {      
		//Brutal force placement
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
void Play::autoPlay(const char& player)
{
	if (game.isGameAliveAI(player) == false)
		return;

	//init
	game.setPlayer(player);
	Shape selected;

	//select a shape
	int shapeID = rand()%21;
	// shape is unavailable or shape can't be placed
	while (game.isPieceUse(shapeID) || !game.hasPlaceToPut(shapeID, player))
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

//Playing mode of 2 human players.
void Play::twoPlayers()
{
	bool checkDead[2] = {0};
	int player = 0;
	bool quit = false;
	while (true) {
		cout << endl;
		cout << "in side" << endl;
		if (!checkDead[player]) {
			char ptmp = 'A' + player;
			this->game.setPlayer(ptmp);
			if (!this->game.isGameAlive(ptmp)) {
				//cout << "wow we find out you're dead!" << endl;
				checkDead[player] = true;
				if (checkDead[ 1-player ]) {
					// we already know this player can't play, check if the other can't play, either.
					cout << "Game is ended." << endl;
					return;
				}
			}
			else
				quit = playerPlay(ptmp);
		}
		if (quit) return;
		player = 1 - player;
	}
}

//Playing mode of human v.s. Artificial Idiot
void Play::playerAI()
{
	bool checkDead[2] = {0};
	int player = 0;
	bool quit = false;
	while (true) {
		cout << endl;
		cout << "in side" << endl;
		if (!checkDead[player]) {
			char ptmp = 'A' + player;
			this->game.setPlayer(ptmp);
			if (!this->game.isGameAlive(ptmp)) {
				//cout << "wow we find out you're dead!" << endl;
				checkDead[player] = true;
				if (checkDead[ 1-player ]) {
					// we already know this player can't play, check if the other can't play, either.
					cout << "Game is ended." << endl;
					return;
				}
			}
			else {
				if (player==0)	// A
					quit = playerPlay('A');
				else
					autoPlay('B');
			}
		}
		if (quit) return;
		player = 1 - player;
	}
}

//mode of two Artificial Idiots battle.
void Play::twoAIs()
{
/*
	bool turn = 0;// A
	char player = (turn == 0) ? 'A' : 'B';
	string junk;
	while (game.isGameAliveAI('A') == true || game.isGameAliveAI('B') == true) {
	// 	game.setPlayer(player);
	// 	autoPlay(player);
	// 	turn = !turn;
	// 	cin >> junk;
	// 	player = (turn == 0) ? 'A' : 'B';
	}
*/
	bool checkDead[2] = {0};
	int player = 0;
	while (true) {
		cout << endl;
		cout << "in side" << endl;
		if (!checkDead[player]) {
			char ptmp = 'A' + player;
			this->game.setPlayer(ptmp);
			if (!this->game.isGameAlive(ptmp)) {
				//cout << "wow we find out you're dead!" << endl;
				checkDead[player] = true;
				if (checkDead[ 1-player ]) {
					// we already know this player can't play, check if the other can't play, either.
					cout << "Game is ended." << endl;
					return;
				}
			}
			else
				autoPlay(ptmp);
		}
		player = 1 - player;
	}
}

void Play::priorityAdvantage()
{
	int winA = 0, winB = 0, times;
	cout << "|---------------------------------|" << endl;
	cout << "|   " << endl << "| Select Number of Games:" << "\n|\n";
	cout << "|\t1) 1K\n|\t2) 10K\n|\t3) 100K\n|" << endl;
	cout << "|--------------------------------- \n";
	cout << "Blokus>>";

	cin >> times;
	if (times == 1) times = 1000;
	else if (times == 2) times = 10000;
	else if (times == 3) times = 100000;

	bool change = false;
	while (times--) {
		this->game.init();
		twoAIs();
		cout << times << " to go....";
		if (this->game.winner() == "A")
			winA++;
		else
			winB++;
		change = !change;
	}

	cout << "|---------------------------------| " << endl;
	cout << "|   " << endl << "| Result :" << "\n|\n";
	cout << "| " << winA << " : " << winB << "\n|" << endl;
	cout << "|   " << endl << "| Best Game :" << "\n|\n";
	cout << "| " << this->game.getBstRngA() << " : " << this->game.getBstRngB() << "\n|" << endl;
	cout << "|--------------------------------- \n";
}

void Play::printBoard()
{
	this->game.printBoard();
}

string Play::winner()
{
	return this->game.winner();
}

