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
	this->deadPlayer = 0;
	this->player = 'A';
	this->turn = false;

	this->selectShape = false;
	this->selected = this->game.getShape(0);
}

//Playing mode of 2 human players.
void Play::twoPlayers()
{
	int instr;
	int isPlayerDead[2] = {0};
	int checkDead;
	while (true) {
		cout << endl;

		if (this->turn) {
			cout << "in side" << endl;
			//this->player = (this->player=='B')? 'A': 'B';
			if (this->player=='B') {
				this->player = 'A';
				checkDead = 0;
			} else {
				this->player = 'B';
				checkDead = 1;
			}
			this->turn = false;
			this->selectShape = false;
			this->game.setPlayer(this->player);

			// if we need to check this person`s placement condition
			if (!isPlayerDead[checkDead]) {
				//cout << "this plyer not dead yet" << endl;
				if(!this->game.isGameAlive(this->player)) {
					//cout << "wow we find out you`re dead!" << endl;
					isPlayerDead[checkDead] = 1;	// mark this player can`t play anymore.
					this->turn = true;
					continue;
				}
			} else {
				//cout << "this plyer dead already" << endl;
				// we already know this player can`t play, check if all two can`t play.
				if(isPlayerDead[0]==1 && isPlayerDead[1]==1) {
					cout << "Game is ended." << endl;
					return;
				}
				this->turn = true;
			}
		}
		
		//this->deadPlayer = 0;
		cout << "|--------------------------------- \n|" << endl;
		cout << "| [instruction #" << this->instrCounter << "] you can press 1~7:" << "\n|\n";
		cout << "|\t1) Select a shape\n|\t2) Flip\n|\t3) Rotate clockwise\n|\t4) Next move\n|\t5) Print the board\n|\t6) List remaining shapes\n|\t7) Check the condition\n|\t999) EXIT\n|\n";
		cout << "|--------------------------------- " << endl;
		cout << " Blockus>>";

		cin >> instr;
		if (instr == 999)
			break;
		if (instr == 1) {		// Select a shape
			this->selectShape = true;
			cout<<"shape index:";
			int tmpID;
			cin >> tmpID;

			if (this->game.checkShapeID(tmpID)) {
				if (this->game.isPieceUse(tmpID)) {
					cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
					continue;
				}
				else {
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
			cout << "[ " << this->player << "'s turn ] input x, y:";
			cin >> x >> y;
			if ( this->game.playerMove(this->selected, this->shapeID, this->player, x, y) ) {
				this->game.setPieceUse(this->shapeID);
				this->instrCounter++;
				this->turn = true;
			}
			else
				cout << this->game.getErrMsg() << endl;
		}
		else if (instr == 5) {	// Print the board
			this->game.printBoard();
		}
		else if (instr == 6) {	// List remaining shapes
			this->game.listShapes(this->player);
		}
		else if (instr == 7) {	// Check the condition
			this->game.isGameAlive(this->player);
		}
		else {
			cout<<"Not a command."<<endl;
		}
	}
}

//mode of two Artificial Idiots battle.
void Play::twoAIs()
{
	ai.twoAIs();
}

//Playing mode of human v.s. Artificial Idiot
void Play::playerAI()
{
	int instr;

	while (true) {
		cout << endl;
		
		if (this->turn) {
			this->player = 'B';
			this->selectShape = false;
			this->game.setPlayer('B');

			if (!this->game.isGameAlive('B')) {
				this->deadPlayer++;

				// check if player still have move to implement.
				if (this->deadPlayer == 2) {
					cout << "Game is ended." << endl;
					return;
				}
			}
			else
				ai.autoPlay('B');

			this->player = 'A';
			this->turn = false;
			this->selectShape = false;
			this->game.setPlayer('A');

			if (!this->game.isGameAlive('A')) {
				this->deadPlayer++;
				this->turn = true;

				// check if player still have move to implement.
				if (this->deadPlayer == 2) {
					cout << "Game is ended." << endl;
					return;
				}
				continue;
			}
		}

		// A's turn:
		this->deadPlayer = 0;
		cout << "|--------------------------------- \n|" << endl;
		cout << "| [instruction #" << this->instrCounter << "] you can press 1~7:" <<"\n|\n";
		cout << "|\t1) Select a shape\n|\t2) Flip\n|\t3) Rotate clockwise\n|\t4) Next move\n|\t5) Print the board\n|\t6) List remaining shapes\n|\t7) Check the condition\n|\t999) EXIT\n|\n";
		cout << "|--------------------------------- " << endl;
		cout << " Blockus>>";

		cin >> instr;
		if (instr == 999)
			break;
		if (instr == 1) {		// Select a shape
			this->selectShape = true;
			cout << "shape index:";
			int tmpID;
			cin >> tmpID;

			if (this->game.checkShapeID (tmpID)) {
				if (this->game.isPieceUse(tmpID)) {
					cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
					continue;
				}
				else {
					this->shapeID = tmpID;
					this->selected = this->game.getShape(this->shapeID);
					this->selected.printShape();
				}
			}
			else {
				cout << "no this index! re do instruction!." << endl;
				continue;
			}
		}
		else if (instr == 2) {	// Flip
			this->selected.flip();
			this->selected.printShape();
		}
		else if (instr == 3) { // Rotate clockwise
			this->selected.turnClockwise();
			this->selected.printShape();
		}
		else if (instr == 4) { // Next move
			if (this->selectShape == false) {	//Hasn't select yet
				cout<<"Please Select a shape."<<endl;
				continue;
			}
			cout << "shapeID:" << this->shapeID << endl;
			this->game.printBoard();
			this->selected.printShape();

			int x, y;
			cout << "[ " << this->player << "'s turn ] input x, y:";
			cin >> x >> y;
			if ( this->game.playerMove(this->selected, this->shapeID, this->player, x, y) ) {
				this->game.setPieceUse(this->shapeID);
				this->instrCounter++;
				this->selectShape = false;
				this->turn = !this->turn;
			}
			else
				cout << this->game.getErrMsg() << endl;
		}
		else if (instr == 5) {	// Print the board
			this->game.printBoard();
		}
		else if (instr == 6) {	// List remaining shapes
			this->game.listShapes(this->player);
		}
		else if (instr == 7) {	// Check the condition
			this->game.isGameAlive(this->player);
		}
		else {
			cout<<"Not a command."<<endl;
		}
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
		ai.twoAIs();
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

