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
	this->instrCounter = 0;
	this->selected = this->game.getShape(0);
    this->turn = true;
    this->isSelect = false;
    this->endCounter = 0;
}

//Playing mode of 2 human players.
void Play::twoPlayers()
{
    int instr;
    bool legalMove = false;

    while (true) {
    	cout << endl;
        this->player = (this->turn)? 'A': 'B';
        this->game.setPlayer(this->player);

        // check if player still have move to implement.
        if (this->endCounter == 2) {
            cout << "Game is ended." << endl;
            return;
        }
        if (this->game.isGameEnd(this->player) == false) {
            this->isSelect = false;
            this->turn = !this->turn;
            this->endCounter++;
        }
        else {
            this->endCounter = 0;
	        cout << "| [instruction #" << instrCounter << "] you can press 1~7:" << "\n|\n";
            cout << "|\t1) Select a shape\n|\t2) Flip\n|\t3) Rotate clockwise\n|\t4) Next move\n|\t5) Print the board\n|\t6) List remaining shapes\n|\t7) Check the condition\n|\t999) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";

	        cin >> instr;
	        if (instr == 999)
	            break;
	        if (instr == 1) {		// select shape.
	            this->isSelect = true;
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
	        	if (this->isSelect == false) {
	        		cout << "Please Select a shape." << endl;
	                continue;
	        	}
	            this->selected.flip();
	            this->selected.printShape();
	        }
	        else if (instr == 3) { // Turn
	        	if (this->isSelect == false) {
	        		cout << "Please Select a shape." << endl;
	                continue;
	        	}
	            this->selected.turnClockwise();
	            this->selected.printShape();
	        }
	        else if (instr == 4) { //player_move.
	            cout << "shapeID:" << this->shapeID << endl;
	            this->game.printBoard();
	            if (this->isSelect == false) {	//Hasn't select yet
	                cout << "Please Select a shape." << endl;
	                continue;
	            }
	            this->selected.printShape();
	            int x, y;
                cout << "[ " << this->player << "'s turn ] input x, y:";
                cin >> x >> y;
	            legalMove = this->game.playerMove(this->selected, this->shapeID, this->player, x, y);
	            if (legalMove == true) {
	            	this->game.setPieceUse(this->shapeID);
	            	this->instrCounter++;
	                this->isSelect = false;
	                this->turn = !this->turn;
	            }
	        }
	        else if (instr == 5) {	//map.
	            this->game.printBoard();
	        }
	        else if (instr == 6) {	//list shape.
	            this->game.listShapes(this->player);
	        }
	        else if (instr == 7) {
	        	this->game.isGameEnd(this->player);
	        }
	        else {
	            cout<<"Not a command."<<endl;
	        }
	    }
    }

}

//Playing mode of human v.s. Artificial Idiot
void Play::playerAI()
{
    int instr;
    bool legalMove = false;

    while (true) {
        if (this->turn == 0) {
            ai.autoPlay('B');
            this->turn = !this->turn;
            continue;
        }
    	cout << endl;
        this->player = (this->turn)?'A':'B';
        this->game.setPlayer(this->player);

        // check if player still have move to implement.
        if (this->endCounter == 2) {
            cout << "Game is ended." << endl;
            return;
        }
        if (this->game.isGameEnd(this->player) == false) {
            this->isSelect = false;
            this->turn = !this->turn;
            this->endCounter++;
        }
        else {
            this->endCounter = 0;
	        cout << "| [instruction #" << this->instrCounter << "] you can press 1~7:" <<"\n|\n";
            cout << "|\t1) Select a shape\n|\t2) Flip\n|\t3) Rotate clockwise\n|\t4) Next move\n|\t5) Print the board\n|\t6) List remaining shapes\n|\t7) Check the condition\n|\t999) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";

	        cin >> instr;
	        if (instr == 999)
	            break;
	        if (instr == 1) {		// select shape.
	            this->isSelect = true;
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
	        else if (instr == 3) { // Turn
	            this->selected.turnClockwise();
	            this->selected.printShape();
	        }
	        else if (instr == 4) { //player_move.
	            cout << "shapeID:" << this->shapeID << endl;
	            this->game.printBoard();
	            if (this->isSelect == false) {	//Hasn't select yet
	                cout<<"Please Select a shape."<<endl;
	                continue;
	            }
	            this->selected.printShape();

	            int x, y;
                cout << "[ " << this->player << "'s turn ] input x, y:";
                cin >> x >> y;
	            legalMove = this->game.playerMove(this->selected, this->shapeID, this->player, x, y);
	            if (legalMove == true) {
	                this->game.setPieceUse(this->shapeID);
	            	this->instrCounter++;
	                this->isSelect = false;
	                this->turn = !this->turn;
	            }
	        }
	        else if (instr == 5) {	//map.
	            this->game.printBoard();
	        }
	        else if (instr == 6) {	//list shape.
	            this->game.listShapes(this->player);
	        }
	        else if (instr == 7) {
	        	this->game.isGameEnd(this->player);
	        }
	        else {
	            cout<<"Not a command."<<endl;
	        }
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
    cout << "| " << this->game.getBestA() << " : " << this->game.getBestB() << "\n|" << endl;
    cout << "|--------------------------------- \n";
}

void Play::init()
{
	this->game.init();
}

void Play::printBoard()
{
	this->game.printBoard();
}

string Play::winner()
{
	return this->game.winner();
}

